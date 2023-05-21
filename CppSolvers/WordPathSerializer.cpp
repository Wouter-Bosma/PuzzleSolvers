#include "WordPathSerializer.h"
#include <sstream>

std::string WordPathSerializer::serialize(const std::vector<std::string>& input)
{
	if (input.size() > 1)
	{
		std::ostringstream stream;
		stream << "WORDPATH;SUCCESS;" << input.size();
		for (const auto& word : input)
		{
			stream << ";" << word;
		}
		return stream.str();
	}
	return "WORDPATH;FAILED;No path found.";
}

std::unique_ptr<WordPathChallenge> WordPathSerializer::deserialize(const std::string& input) const
{
	//WORDPATH;DEPTH;FIRST;SECOND
	//WORDPATH;SHORT;FIRST;SECOND
	std::stringstream inputStream(input);
	std::string token;
	std::unique_ptr<WordPathChallenge> wpc = std::make_unique<WordPathChallenge>();
	int tokenCount = 0;
	while (getline(inputStream, token, ';'))
	{
		if (tokenCount == 0)
		{
			if(token == "DEPTH")
			{
				wpc->depthSearch = true;
			}
			else if (token == "SHORT")
			{
				wpc->depthSearch = false;
			}
			else
			{
				throw std::exception("No valid wordpath challenge strategy defined, only DEPTH and SHORT are available.");
			}
			++tokenCount;
			continue;
		}
		if (tokenCount == 1)
		{
			wpc->startWord = std::move(token);
			++tokenCount;
			continue;
		}
		if (tokenCount == 2)
		{
			wpc->endWord = std::move(token);
			++tokenCount;
			continue;
		}
		throw std::exception("Too many arguments found for deserializing.");
	}

	const auto startSize = wpc->startWord.size();
	const auto endSize = wpc->endWord.size();
	if (startSize != endSize)
	{
		throw std::exception("Start and end word should have the same length.");
	}
	wpc->size = startSize;
	return wpc;
}
