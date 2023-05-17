#include "SudokuSerializer.h"
string SudokuSerializer::serialize(const vector<vector<int>>& input)
{
	std::ostringstream stream;
	stream << input.size();
	for (auto& singleVector : input)
	{
		stream << ";" << singleVector.size();
		for (auto& val : singleVector)
		{
			stream << ";" << val;
		}
	}
	return stream.str();
}

vector<vector<int>> SudokuSerializer::deserialize(const string& input)
{
	std::istringstream stream(input);
	int size;
	char seperator;
	stream >> size;
	stream >> seperator;
	auto result = std::vector<vector<int>>(size);
	for (int i = 0; i < size; ++i)
	{
		int vectorSize;
		stream >> vectorSize;
		stream >> seperator;
		vector<int> temp(vectorSize);
		for (int j = 0; j < vectorSize; ++j)
		{
			stream >> temp[j];
			stream >> seperator;
		}
		result[i] = std::move(temp);
	}
	return result;
}