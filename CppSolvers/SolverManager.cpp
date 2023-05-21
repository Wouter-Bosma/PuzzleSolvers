// SudokuSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "OptimizedSudokuSolver.h"
#include "Connector.h"
#include <future>
#include <IOStream>

#include "SudokuTester.h"
#include "WordPath.h"
#include "WordPathSolvers.h"

int main(int argc, char* argv[])
{
	if (argc != 1)
	{
		if (argc == 2 && (*argv[1] == 'T' || *argv[1] == 't'))
		{
			SudokuTester st{};
			st.basicTests();
			WordPath wp("4letters.txt", 4);
			auto res = wp.solve("WORDPATH;SHORT;QUIZ;STOP");
			return 0;
		}
		std::cout << "Only T is accepted as command line parameter at the moment for testing purposes.";
		return 0;
	}
	
	Connector connector;
	std::unique_ptr<ISolver> ossp = std::make_unique<OptimizedSudokuSolver>();
	connector.setSolver("SUDOKU", std::move(ossp));

	std::unique_ptr<ISolver> wps = std::make_unique<WordPathSolvers>();
	connector.setSolver("WORDPATH", std::move(wps));

	connector.connectServer();

	//TODO: Add disconnect behavior.
}
