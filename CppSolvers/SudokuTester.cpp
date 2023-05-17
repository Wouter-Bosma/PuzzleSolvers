#include "SudokuTester.h"

#include <iostream>
#include <chrono>
#include "BasicSudokuSolver.h"
#include "OptimizedSudokuSolver.h"
//Essentially a class with some functions used to test the sudoku initially.


using std::vector;
using namespace std::chrono_literals;

void SudokuTester::solveBasicTestSudoku(bool showResult)
{
	/**/vector<int> row0 = { 0,2,0,5,0,1,0,9,0 };
	vector<int> row1 = { 8,0,0,2,0,3,0,0,6 };
	vector<int> row2 = { 0,3,0,0,6,0,0,7,0 };
	vector<int> row3 = { 0,0,1,0,0,0,6,0,0 };
	vector<int> row4 = { 5,4,0,0,0,0,0,1,9 };
	vector<int> row5 = { 0,0,2,0,0,0,7,0,0 };
	vector<int> row6 = { 0,9,0,0,3,0,0,8,0 };
	vector<int> row7 = { 2,0,0,8,0,4,0,0,7 };
	vector<int> row8 = { 0,1,0,9,0,7,0,6,0 };/**/
	/*vector<int> row0 = { 1,0,0,0,0,0,0,0,0 };
	vector<int> row1 = { 0,2,0,0,0,0,0,0,0 };
	vector<int> row2 = { 0,0,3,0,0,0,0,0,0 };
	vector<int> row3 = { 0,0,0,4,0,0,0,0,0 };
	vector<int> row4 = { 9,8,7,0,5,0,3,2,1 };
	vector<int> row5 = { 0,0,0,0,0,6,0,0,0 };
	vector<int> row6 = { 0,0,0,0,0,0,7,0,0 };
	vector<int> row7 = { 0,0,0,0,0,0,0,8,0 };
	vector<int> row8 = { 0,0,0,0,0,0,0,0,9 };/**///Negative Sudoku test

	vector inputSudoku = { row0, row1, row2, row3, row4, row5, row6, row7, row8 };

	//Serializer ser;
	//auto temp = ser.serialize(inputSudoku);
	//std::cout << temp;
	//SudokuConnector sc;
	//sc.connectServer();

	//auto sudokuDes = ser.deserialize(temp);

	try
	{
		BasicSudokuSolver BSS;
		auto result = BSS.solveSudoku(inputSudoku);
		if (!showResult) return;
		std::cout << "Solved Basic: " << result << std::endl;
		if (result)
		{
			for (auto& row : inputSudoku)
			{
				for (auto& cell : row)
				{
					std::cout << cell << " ";
				}
				std::cout << std::endl;
			}
		}
	}
	catch (std::exception& ex)
	{
		std::cout << "Solving failed: " << ex.what() << std::endl;
	}

}

void SudokuTester::solveOptimizedTestSudoku(bool showResult)
{
	/**/vector<int> row0 = { 0,2,0,5,0,1,0,9,0 };
	vector<int> row1 = { 8,0,0,2,0,3,0,0,6 };
	vector<int> row2 = { 0,3,0,0,6,0,0,7,0 };
	vector<int> row3 = { 0,0,1,0,0,0,6,0,0 };
	vector<int> row4 = { 5,4,0,0,0,0,0,1,9 };
	vector<int> row5 = { 0,0,2,0,0,0,7,0,0 };
	vector<int> row6 = { 0,9,0,0,3,0,0,8,0 };
	vector<int> row7 = { 2,0,0,8,0,4,0,0,7 };
	vector<int> row8 = { 0,1,0,9,0,7,0,6,0 };/**/
	/*vector<int> row0 = { 1,0,0,0,0,0,0,0,0 };
	vector<int> row1 = { 0,2,0,0,0,0,0,0,0 };
	vector<int> row2 = { 0,0,3,0,0,0,0,0,0 };
	vector<int> row3 = { 0,0,0,4,0,0,0,0,0 };
	vector<int> row4 = { 9,8,7,0,5,0,3,2,1 };
	vector<int> row5 = { 0,0,0,0,0,6,0,0,0 };
	vector<int> row6 = { 0,0,0,0,0,0,7,0,0 };
	vector<int> row7 = { 0,0,0,0,0,0,0,8,0 };
	vector<int> row8 = { 0,0,0,0,0,0,0,0,9 };/**/

	vector inputSudoku = { row0, row1, row2, row3, row4, row5, row6, row7, row8 };

	try
	{
		OptimizedSudokuSolver OSS;
		auto result = OSS.solveSudoku(inputSudoku);
		if (!showResult) return;
		std::cout << "Solved Optimized: " << result << std::endl;
		if (result)
		{
			for (auto& row : inputSudoku)
			{
				for (auto& cell : row)
				{
					std::cout << cell << " ";
				}
				std::cout << std::endl;
			}
		}
	}
	catch (std::exception& ex)
	{
		std::cout << "Solving failed: " << ex.what() << std::endl;
	}

}

void SudokuTester::basicTests()
{

	/*SudokuConnector connector;
	auto server = std::async(std::launch::async, [&]() {connector.connectServer(); });
	auto client = std::async(std::launch::async, [&]() {connector.connectClient(); });

	server.wait();
	server.wait();
	std::this_thread::sleep_for(1000ms);
	std::cout << "Finished" << std::endl;
	return 0;*/
	{
		auto now = std::chrono::high_resolution_clock::now();
		solveOptimizedTestSudoku(false);
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - now);
		std::cout << "Duration Optimized: " << duration.count() << std::endl;
	}

	{
		auto now = std::chrono::high_resolution_clock::now();
		solveBasicTestSudoku(false);
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - now);
		std::cout << "Duration Basic: " << duration.count() << std::endl;
	}

	{
		auto now = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 10000; ++i)
		{
			solveBasicTestSudoku(false);
		}
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - now);
		std::cout << "Duration Basic: " << duration.count() / 10000.0 << std::endl;
	}

	{
		auto now = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 10000; ++i)
		{
			solveOptimizedTestSudoku(false);
		}
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - now);
		std::cout << "Duration Optimized: " << duration.count() / 10000.0 << std::endl;
	}

	{
		auto now = std::chrono::high_resolution_clock::now();
		solveBasicTestSudoku(false);
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - now);
		std::cout << "Duration Basic: " << duration.count() << std::endl;
	}

	{
		auto now = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 10000; ++i)
		{
			solveBasicTestSudoku(false);
		}
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - now);
		std::cout << "Duration Basic: " << duration.count() / 10000.0 << std::endl;
	}

	{
		auto now = std::chrono::high_resolution_clock::now();
		solveOptimizedTestSudoku(false);
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - now);
		std::cout << "Duration Optimized: " << duration.count() << std::endl;
	}

	{
		auto now = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 10000; ++i)
		{
			solveOptimizedTestSudoku(false);
		}
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - now);
		std::cout << "Duration Optimized: " << duration.count() / 10000.0 << std::endl;
	}
}