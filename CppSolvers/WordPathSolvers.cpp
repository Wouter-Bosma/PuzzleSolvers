#include "WordPathSolvers.h"

#include <IOStream>

WordPathSolvers::WordPathSolvers()
{
	std::unique_ptr<WordPath> wp4 = std::make_unique<WordPath>("4letters.txt", 4);
	std::unique_ptr<WordPath> wp5 = std::make_unique<WordPath>("5letters.txt", 5);
	std::unique_ptr<WordPath> wp6 = std::make_unique<WordPath>("6letters.txt", 6);
	wordPathSolvers[4] = std::move(wp4);
	wordPathSolvers[5] = std::move(wp5);
	wordPathSolvers[6] = std::move(wp6);
}

std::string WordPathSolvers::solve(std::string& input)
{
	WordPathSerializer wps;
	auto challenge = wps.deserialize(input);

	try
	{
		auto solver = wordPathSolvers.find(challenge->size);
		if (solver == wordPathSolvers.end())
		{
			return "WORDPATH;FAILED;Invalid puzzle size given.";
		}
		const auto result = solver->second->solve(std::move(challenge));
		return WordPathSerializer::serialize(result);
	}
	catch(std::exception& ex)
	{
		const std::string result = "WORDPATH;FAILED;";
		const auto reason = ex.what();
		return result + reason;
	}
}