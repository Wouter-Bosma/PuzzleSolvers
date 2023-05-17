#include "BasicSudokuSolver.h"

bool BasicSudokuSolver::solveSudoku(vector<vector<int>>& inputSudoku)
{
	validateSudoku(inputSudoku);
	return solveSudoku(inputSudoku, 0, 0);
}

bool BasicSudokuSolver::solveSudoku(vector<vector<int>>& inputSudoku, const int& row, const int& column)
{
	if (column == 8 && row == 8)
	{
		return checkExitCriteria(inputSudoku);
	}

	int nextRow, nextColumn;
	getNextRowColumn(row, column, nextRow, nextColumn);
	
	if (inputSudoku[row][column] != 0)
	{
		return solveSudoku(inputSudoku, nextRow, nextColumn);
	}
	return checkIfThisSquareCanBeSolved(inputSudoku, row, column, nextRow, nextColumn);
}

bool BasicSudokuSolver::checkSudoku(const vector<vector<int>>& inputSudoku, const int& row, const int& column)
{
	return checkValidRow(inputSudoku, row) && checkValidColumn(inputSudoku, column) && checkValidSquare(inputSudoku, getSquare(row, column));
}

bool BasicSudokuSolver::checkExitCriteria(vector<vector<int>>& inputSudoku)
{
	if (inputSudoku[8][8] != 0)
	{
		return true;
	}
	for (int i = 1; i <= 9; ++i)
	{
		inputSudoku[8][8] = i;
		if (checkSudoku(inputSudoku, 8, 8))
		{
			return true;
		}
	}
	return false;
}

bool BasicSudokuSolver::checkIfThisSquareCanBeSolved(vector<vector<int>>& inputSudoku, const int& row, const int& column,  const int& nextRow, const int& nextColumn)
{
	for (int i = 1; i <= 9; ++i)
	{
		inputSudoku[row][column] = i;
		if (checkSudoku(inputSudoku, row, column))
		{
			if (solveSudoku(inputSudoku, nextRow, nextColumn))
			{
				return true;
			}
		}
	}
	inputSudoku[row][column] = 0;
	return false;
}