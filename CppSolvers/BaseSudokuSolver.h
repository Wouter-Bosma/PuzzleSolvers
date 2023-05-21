#pragma once
#include <vector>
#include "ISolver.h"
#include <string>

using std::vector;

class BaseSudokuSolver : public virtual ISolver
{
public:
	BaseSudokuSolver();
	std::string solve(std::string& request) override;

	virtual bool solveSudoku(vector<vector<int>>& inputSudoku) = 0;
	virtual ~BaseSudokuSolver() = default;

protected:
	static int getSquare(const int& row, const int& column);
	static void getRowColumn(int square, int posInSquare, int& row, int& column);
	static void validateSudoku(const vector<vector<int>>& inputSudoku);
	static bool checkValidRow(const vector<vector<int>>& input, int row);
	static bool checkValidColumn(const vector<vector<int>>& input, int column);
	static bool checkValidSquare(const vector<vector<int>>& input, int square);
	static void getNextRowColumn(const int row, const int column, int& nextRow, int& nextColumn);

private:
	inline static bool initialized = false;
	inline static int rowColumnToSquare[81];
	inline static int squareToRow[81];
	inline static int squareToColumn[81];
};
