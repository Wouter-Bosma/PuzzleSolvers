#pragma once
#include <unordered_set>
#include <string>
#include <unordered_map>
#include <deque>

#include "WordPathSerializer.h"

class WordPath
{
public:
	WordPath(const std::string& filePath, int wordSize);
	std::string solve(std::string input);
	std::vector<std::string> solve(std::unique_ptr<WordPathChallenge>&&);

private:
	std::vector<std::string> depthSearch(std::string start, std::string final);
	std::vector<std::string> shortSearch(std::string start, std::string final);

	bool depthRecursiveSearch(std::string& start, std::string& final, std::unordered_set<std::string>& memo, std::vector<std::string>& result);
	bool currentValid(const std::string& current, const std::unordered_set<std::string>& memo);

	static void uppercaseWords(char* buffer, const uintmax_t& size);
	void moveWordsToSet(char* buffer, const uintmax_t& size);
	void readListOfWords(const std::string& fileName);

	bool findShortestPath(std::unordered_map<std::string, std::string>& startMap, std::unordered_map<std::string, std::string>& targetMap, std::deque<std::string>& result);
	void oneStepWords(const std::string& word, std::unordered_map<std::string, std::string>& newItems);
	std::string intersect(std::unordered_map<std::string, std::string>& startMap, std::unordered_map<std::string, std::string>& targetMap);
	void enhance(std::unordered_map<std::string, std::string>& toEnhance);

	int wordSize;
	std::unordered_set<std::string> words;
	WordPathSerializer serializer;
};

