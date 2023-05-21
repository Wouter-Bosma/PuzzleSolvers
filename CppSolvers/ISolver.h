#pragma once
#include <string>

class ISolver
{
public:
	virtual std::string solve(std::string&) = 0;
};

