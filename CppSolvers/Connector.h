#pragma once
#include "zmq.hpp"
#include <string>
#include "ISolver.h"
#include <unordered_map>

class Connector
{
public:
    void connectServer();
    void setSolver(std::string solverId, std::unique_ptr<ISolver> solver);
private:
    std::pair<std::string, std::string> split(const std::string& input, char token);
    std::unordered_map<std::string, std::unique_ptr<ISolver>> solvers;
};

