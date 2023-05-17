#pragma once
#include "BaseSudokuSolver.h"

class OptimizedSudokuSolver : public virtual BaseSudokuSolver
{
public:
	bool solveSudoku(vector<vector<int>>& inputSudoku) override;
	
private:
	bool solveSudoku(vector<vector<int>>& inputSudoku, const int row, const int column);
	void fillAvailableRows(const vector<vector<int>>& inputSudoku);
	void fillAvailableColumns(const vector<vector<int>>& inputSudoku);
	void fillAvailableSquares(const vector<vector<int>>& inputSudoku);
	bool checkExitCriteria(vector<vector<int>>& inputSudoku);
	bool checkIfThisSquareCanBeSolved(vector<vector<int>>& inputSudoku, const int& row, const int& column, const int& nextRow, const int& nextColumn);
	bool checkValidity(vector<vector<int>>& inputSudoku, const int row, const int column);
	//vector<vector<bool>> is optimized for space not performance (ie. bit wise storage) hence vector<vector<int>> is more performant.
	//vector<vector<int>> availableNumsRows = vector<vector<int>>(9, (vector<int>(9, 1)));
	//vector<vector<int>> availableNumsColumns = vector<vector<int>>(9, (vector<int>(9, 1)));
	//vector<vector<int>> availableNumsSquares = vector<vector<int>>(9, (vector<int>(9, 1)));
	//However straight arrays are of course faster as vectors.

	int availableRows[81]{};
	int availableColumns[81]{};
	int availableSquares[81]{};
};

