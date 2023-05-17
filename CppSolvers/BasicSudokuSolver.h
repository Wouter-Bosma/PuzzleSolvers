#pragma once
#include "BaseSudokuSolver.h"
#include <vector>
using std::vector;

class BasicSudokuSolver : public virtual BaseSudokuSolver
{
public:
	bool solveSudoku(vector<vector<int>>& inputSudoku) override;
	
private:
	static bool solveSudoku(vector<vector<int>>& inputSudoku, const int& column, const int& row);
	static bool checkSudoku(const vector<vector<int>>& input, const int& row, const int& column);
	static bool checkExitCriteria(vector<vector<int>>& inputSudoku);
	static bool checkIfThisSquareCanBeSolved(vector<vector<int>>& inputSudoku, const int& row, const int& column, const int& nextRow, const int& nextColumn);
};

