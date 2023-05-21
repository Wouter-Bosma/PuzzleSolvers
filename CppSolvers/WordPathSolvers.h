#pragma once
#include <unordered_map>

#include "ISolver.h"
#include "WordPath.h"

class WordPathSolvers : public virtual ISolver
{
public:
	WordPathSolvers();
	std::string solve(std::string& input) override;

private:
	std::unordered_map<int, std::unique_ptr<WordPath>> wordPathSolvers;
};

