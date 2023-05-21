#include "WordPath.h"

#include <filesystem>
#include <fstream>
#include <IOStream>

WordPath::WordPath(const std::string& filePath, int wordSize)
{
	this->wordSize = wordSize;
	readListOfWords(filePath);
}

std::string WordPath::solve(std::string input)
{
	return WordPathSerializer::serialize(solve(serializer.deserialize(input)));
}

std::vector<std::string> WordPath::solve(std::unique_ptr<WordPathChallenge>&& challenge)
{
	return challenge->depthSearch ? depthSearch(challenge->startWord, challenge->endWord) : shortSearch(challenge->startWord, challenge->endWord);
}

void WordPath::readListOfWords(const std::string& fileName)
{
	auto file = std::filesystem::current_path() / "Resources" / fileName;
	if (!std::filesystem::exists(file)) file = std::filesystem::current_path() / fileName;
	std::cout << "Get file size: " << file << std::endl;
	auto size = std::filesystem::file_size(file);
	char* buffer = new char[size];
	std::cout << "Open file with size: " << size << std::endl;
	std::ifstream fin(file, std::ios::in | std::ios::binary);
	std::cout << "Read file into buffer." << std::endl;
	fin.read(buffer, size);

	std::cout << "Make uppercase." << std::endl;
	uppercaseWords(buffer, size);
	std::cout << "Move words." << std::endl;
	moveWordsToSet(buffer, size);

	std::cout << "Delete[]" << std::endl;
	delete[] buffer;
}

void WordPath::uppercaseWords(char* buffer, const uintmax_t& size)
{
	for(uintmax_t i = 0; i < size; ++i)
	{
		if (buffer[i] >= 'a' && buffer[i] <= 'z')
		{
			buffer[i] -= 32;
		}
	}
}

void WordPath::moveWordsToSet(char* buffer, const uintmax_t& size)
{
	int wordCount = 0;
	std::string result(wordSize, '\0');
	for(uintmax_t i = 0; i < size; ++i)
	{
		if (wordCount == wordSize)
		{
			if (buffer[i]==';')
			{
				words.emplace(std::move(result));
				result = std::string(wordSize, '\0');
			}
			wordCount = 0;
			continue;
		}
		if (buffer[i]>='A' && buffer[i]<='Z')
		{
			result[wordCount++] = buffer[i];
			continue;
		}
		wordCount = 0;
	}
}

std::vector<std::string> WordPath::depthSearch(std::string start, std::string target)
{
	if (static_cast<int>(start.size()) != wordSize || static_cast<int>(target.size()) != wordSize)
	{
		throw std::exception("Source and target words don't match the indicated word length.");
	}

	std::ranges::transform(start, start.begin(), ::toupper);
	std::ranges::transform(target, target.begin(), ::toupper);

	std::vector<std::string> result;

	if (!words.contains(start) || !words.contains(target))
	{
		return result;
	}

	std::unordered_set<std::string> memo;
	memo.emplace(start);
	depthRecursiveSearch(start, target, memo, result);
	std::reverse(result.begin(), result.end());
	return result;
}

bool checkOneLetterDifference(std::string& word1, std::string& word2)
{
	int count = 0;
	const int size = word1.size();
	for(int x = 0; x < size; ++x)
	{
		count += word1[x] == word2[x] ? 1 : 0;
	}
	return size - count == 1;
}

bool WordPath::currentValid(const std::string& current, const std::unordered_set<std::string>& memo)
{
	return (words.contains(current) && !memo.contains(current));
}

bool WordPath::depthRecursiveSearch(std::string& start, std::string &target, std::unordered_set<std::string>& memo, std::vector<std::string>& result)
{
	//exit criteria
	if(checkOneLetterDifference(start, target))
	{
		result.emplace_back(target);
		result.emplace_back(start);
		return true;
	}

	//Check can move any letter and try from there
	
	for(int i = 0; i < wordSize; ++i)
	{
		std::string current{ start };
		for(char c = 'A'; c <= 'Z'; ++c)
		{
			current[i] = c;
			if (currentValid(current, memo))
			{
				memo.emplace(current);
				if (depthRecursiveSearch(current, target, memo, result))
				{
					result.emplace_back(start);
					return true;
				}
			}
		}
	}
	return false;
}

std::string WordPath::intersect(std::unordered_map<std::string, std::string>& startMap, std::unordered_map<std::string, std::string>& targetMap)
{
	for(auto& start : startMap)
	{
		auto target = targetMap.find(start.first);
		if (target == targetMap.end())
		{
			continue;
		}
		return start.first;//this is the intersecting key
	}
	return "";
}

void WordPath::oneStepWords(const std::string& word, std::unordered_map<std::string, std::string>& newItems)
{
	for(int i = 0; i < wordSize; ++i)
	{
		auto newWord = std::string{ word };
		for(char c = 'A'; c <= 'Z'; ++c)
		{
			if(word[i] == c)
			{
				continue;
			}
			newWord[i] = c;
			if (!words.contains(newWord))
			{
				continue;
			}
			if(newItems.contains(newWord))
			{
				continue;
			}
			newItems[newWord] = word;
		}
	}
}

void WordPath::enhance(std::unordered_map<std::string, std::string>& toEnhance)
{
	std::unordered_map<std::string, std::string> newItems;
	for(auto& item: toEnhance)
	{
		oneStepWords(item.first, newItems);
	}
	for(auto& item : newItems)
	{
		if (!toEnhance.contains(item.first))
		{
			toEnhance[item.first] = item.second;
		}
	}
}


bool WordPath::findShortestPath(std::unordered_map<std::string, std::string>& startMap, std::unordered_map<std::string, std::string>& targetMap, std::deque<std::string>& result)
{
	std::string res;
	auto startCount = 0;
	while (startMap.size() + targetMap.size() != startCount)
	{
		startCount = startMap.size() + targetMap.size();
		auto res = intersect(startMap, targetMap);
		if (!res.empty())
		{
			std::string resTarget = res;
			std::string headitem;
			while ((headitem = (startMap.find(res)->second)) != startMap.find(res)->first)
			{
				result.push_front(headitem);
				res = headitem;
			}
			//result.push_front(start);

			while((headitem = (targetMap.find(resTarget)->second)) != targetMap.find(resTarget)->first)
			{
				result.push_back(resTarget);
				resTarget = headitem;
			}
			result.push_back(headitem);
			return true;
		}
		if (startMap.size() <= targetMap.size())
		{
			enhance(startMap);
		}
		else
		{
			enhance(targetMap);
		}
	}
	return false;
}

std::vector<std::string> WordPath::shortSearch(std::string start, std::string target)
{
	if (static_cast<int>(start.size()) != wordSize || static_cast<int>(target.size()) != wordSize)
	{
		throw std::exception("Source and target words don't match the indicated word length.");
	}

	std::ranges::transform(start, start.begin(), ::toupper);
	std::ranges::transform(target, target.begin(), ::toupper);

	if (start == target || checkOneLetterDifference(start, target))
	{
		auto res = std::vector{ start, target };
		return res;
	}

	std::unordered_map<std::string, std::string> startMap;
	std::unordered_map<std::string, std::string> targetMap;

	startMap[start] = start;
	targetMap[target] = target;

	auto res = std::deque<std::string>();
	findShortestPath(startMap, targetMap, res);
	std::vector<std::string>result = std::vector<std::string>({ res.begin(), res.end() });
	return result;
}