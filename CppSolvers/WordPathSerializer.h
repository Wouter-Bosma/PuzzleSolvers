#pragma once
#include "WordPathChallenge.h"
#include <vector>
#include <future>

class WordPathSerializer
{
public:
	static std::string serialize(const std::vector<std::string>& input);
	std::unique_ptr<WordPathChallenge> deserialize(const std::string& input) const;
};

