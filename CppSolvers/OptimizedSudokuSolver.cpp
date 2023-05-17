#include "OptimizedSudokuSolver.h"

#include <IOStream>

bool OptimizedSudokuSolver::solveSudoku(vector<vector<int>>& inputSudoku)
{
	validateSudoku(inputSudoku);

	for(int i = 0; i < 81; ++i)
	{
		availableColumns[i] = 0;
		availableRows[i] = 0;
		availableSquares[i] = 0;
	}
	fillAvailableRows(inputSudoku);
	fillAvailableColumns(inputSudoku);
	fillAvailableSquares(inputSudoku);
	
	return solveSudoku(inputSudoku, 0, 0);
}

void OptimizedSudokuSolver::fillAvailableRows(const vector<vector<int>>& inputSudoku)
{
	for (int i = 0; i < 9; ++i)
	{
		for (const auto& num : inputSudoku[i])
		{
			if (num != 0)
			{
				availableRows[i * 9 + num - 1] = 1;
			}
		}
	}
}
void OptimizedSudokuSolver::fillAvailableColumns(const vector<vector<int>>& inputSudoku)
{
	for (const auto& vec : inputSudoku)
	{
		for (int i = 0; i < 9; ++i)
		{
			if (vec[i] != 0)
			{
				availableColumns[i * 9 + vec[i] - 1] = 1;
			}
		}
	}
}
void OptimizedSudokuSolver::fillAvailableSquares(const vector<vector<int>>& inputSudoku)
{
	for (int square = 0; square < 9; ++square)
	{
		for (int posInSquare = 0; posInSquare < 9; ++posInSquare)
		{
			int row, column;
			getRowColumn(square, posInSquare, row, column);
			const int& num = inputSudoku[row][column];
			if (num != 0)
			{
				availableSquares[square * 9 + num - 1] = 1;
			}
		}
	}
}

bool OptimizedSudokuSolver::solveSudoku(vector<vector<int>>& inputSudoku, const int row, const int column)
{
	if (column == 8 && row == 8)
	{
		return checkExitCriteria(inputSudoku);
	}

	int nextColumn, nextRow;
	getNextRowColumn(row, column, nextRow, nextColumn);
	
	if (inputSudoku[row][column] != 0)
	{
		return solveSudoku(inputSudoku, nextRow, nextColumn);
	}

	return checkIfThisSquareCanBeSolved(inputSudoku, row, column, nextRow, nextColumn);
}

bool OptimizedSudokuSolver::checkExitCriteria(vector<vector<int>>& inputSudoku)
{
	if (inputSudoku[8][8] != 0)
	{
		return true;
	}
	for (int i = 1; i <= 9; ++i)
	{
		if (0 == availableRows[8 * 9 + i - 1] && 0 == availableColumns[8 * 9 + i - 1] && 0 == availableSquares[8 * 9 + i - 1])
		{
			availableRows[8 * 9 + i - 1] = 1;
			availableColumns[8 * 9 + i - 1] = 1;
			availableSquares[8 * 9 + i - 1] = 1;

			inputSudoku[8][8] = i;
			return true;
		}
	}
	return false;
}

bool OptimizedSudokuSolver::checkValidity(vector<vector<int>>& inputSudoku, const int row, const int column)
{
	for(int row = 0; row < 9; ++row)
	{
		for(int column = 0; column < 9; ++column)
		{
			const int square = getSquare(row, column);
			if (inputSudoku[row][column] != 0)
			{
				continue;
			}
			bool found = false;
			for(int num = 1; num <= 9; ++num)
			{
				if (0 == availableRows[row * 9 + num - 1] && 0 == availableColumns[column * 9 + num - 1] && 0 == availableSquares[square *9 + num - 1])
				{
					found = true;
					break;
				}
			}
			if(!found)
			{
				return false;
			}
		}
	}
	return true;
}

bool OptimizedSudokuSolver::checkIfThisSquareCanBeSolved(vector<vector<int>>& inputSudoku, const int& row, const int& column, const int& nextRow, const int& nextColumn)
{
	const int square = getSquare(row, column);
	for (int i = 1; i <= 9; ++i)
	{
		if (0 == availableRows[row * 9 + i - 1] && 0 == availableColumns[column * 9 + i - 1] && 0 == availableSquares[square * 9 + i - 1])
		{
			availableRows[row * 9 + i - 1] = 1;
			availableColumns[column * 9 + i - 1] = 1;
			availableSquares[square * 9 + i - 1] = 1;
			inputSudoku[row][column] = i;
			if (checkValidity(inputSudoku, row, column))
			{
				if (solveSudoku(inputSudoku, nextRow, nextColumn))
				{
					return true;
				}
			}

			inputSudoku[row][column] = 0;
			availableRows[row * 9 + i - 1] = 0;
			availableColumns[column * 9 + i - 1] = 0;
			availableSquares[square * 9 + i - 1] = 0;
		}
	}
	return false;
}