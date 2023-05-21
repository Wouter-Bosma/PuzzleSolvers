#include "BaseSudokuSolver.h"
#include "SudokuSerializer.h"

std::string BaseSudokuSolver::solve(std::string& request)
{
	auto sudoku = SudokuSerializer::deserialize(request);
	if (solveSudoku(sudoku))
	{
		return "SUCCESS;" + SudokuSerializer::serialize(sudoku);
	}

	return "FAILED;" + request;
}

BaseSudokuSolver::BaseSudokuSolver()
{
	if (!initialized)
	{
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				rowColumnToSquare[i * 9 + j] = ((i / 3) * 3) + (j / 3);

				const int row = (i / 3) * 3 + (j / 3);
				const int column = (i % 3) * 3 + (j % 3);
				squareToRow[i * 9 + j] = row;
				squareToColumn[i * 9 + j] = column;
			}
		}
		initialized = true;
	}
}


void BaseSudokuSolver::validateSudoku(const vector<vector<int>>& inputSudoku)
{
	if (inputSudoku.size() != 9)
	{
		throw std::exception("Input sudoku does not have valid number of rows.");
	}
	for (auto& vec : inputSudoku)
	{
		if (vec.size() != 9)
		{
			throw std::exception("Input sudoku does not have valid number of columns in any of the rows");
		}
		for (const auto& item : vec)
		{
			if (item < 0 || item > 9)
			{
				throw std::exception("Input sudoku not valid, all digits are between 0 or 9. 0 Meaning a blank square");
			}
		}
	}

	for (int check = 0; check < 9; ++check)
	{
		if (!checkValidRow(inputSudoku, check))
		{
			throw std::exception("Input sudoku does have at least one invalid row.");
		}
		if (!checkValidColumn(inputSudoku, check))
		{
			throw std::exception("Input sudoku does have at least one invalid column.");
		}
		if (!checkValidSquare(inputSudoku, check))
		{
			throw std::exception("Input sudoku does have at least one invalid square.");
		}
	}

}

bool BaseSudokuSolver::checkValidRow(const vector<vector<int>>& input, int row)
{
	int valid = 0;
	for (auto& num : input[row])
	{
		if (num != 0)
		{
			const int x = 1 << num;
			if ((x & valid) != 0)
			{
				return false;
			}
			valid |= x;
		}
	}
	return true;
}

bool BaseSudokuSolver::checkValidColumn(const vector<vector<int>>& input, int column)
{
	int valid = 0;
	for (auto& vec : input)
	{
		const int num = vec[column];
		if (num != 0)
		{
			const int x = 1 << num;
			if ((x & valid) != 0)
			{
				return false;
			}
			valid |= x;
		}
	}
	return true;
}

bool BaseSudokuSolver::checkValidSquare(const vector<vector<int>>& input, int square)
{
	//[012]
	//[345]
	//[678]
	const auto startColumn = squareToColumn[square * 9];//(square % 3) * 3;
	const auto startRow = squareToRow[square * 9];//(square / 3) * 3;

	int valid = 0;
	for (int r = 0; r < 3; ++r)
	{
		auto& row = input[r + startRow];
		for (int c = 0; c < 3; ++c)
		{
			const int num = row[(startColumn + c)];
			if (num != 0)
			{
				const int x = 1 << num;
				if ((x & valid) != 0)
				{
					return false;
				}
				valid |= x;
			}
		}
	}
	return true;
}

int BaseSudokuSolver::getSquare(const int& row, const int& column)
{
	//return ((row / 3) * 3) + (column / 3);
	return rowColumnToSquare[row * 9 + column];
}

void BaseSudokuSolver::getRowColumn(int square, int posInSquare, int& row, int& column)
{
	//modulo is notoriously slow so 
	//column = (square % 3) * 3 + (posInSquare % 3);
	//row = (square / 3) * 3 + (posInSquare / 3);
	const int pos = square * 9 + posInSquare;
	row = squareToRow[pos];
	column = squareToColumn[pos];

	//const auto& res = squareToRowColumn[square * 9 + posInSquare];
	//row = res.first;
	//column = res.second;
}

void BaseSudokuSolver::getNextRowColumn(const int row, const int column, int& nextRow, int& nextColumn)
{
	if (column == 8)
	{
		nextColumn = 0;
		nextRow = row + 1;
	}
	else
	{
		nextColumn = column + 1;
		nextRow = row;
	}
}