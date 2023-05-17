#pragma once
#include <vector>
#include <string>
#include <sstream>


using std::vector;
using std::string;

class SudokuSerializer
{
public:
	static string serialize(const vector<vector<int>>& input);
	static vector<vector<int>> deserialize(const string& input);
};

