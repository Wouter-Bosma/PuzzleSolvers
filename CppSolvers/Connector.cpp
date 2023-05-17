#include "Connector.h"
#include <IOStream>

void Connector::connectServer()
{
	// initialize the zmq context with a single IO thread
    zmq::context_t context{ 1 };

    // construct a REP (reply) socket and bind to interface
    zmq::socket_t socket{ context, zmq::socket_type::rep };
    socket.bind("tcp://*:5555");

    for (;;)
    {
        zmq::message_t request;

        socket.recv(request, zmq::recv_flags::none);

        std::string stringRequest = request.to_string();
		std::cout << "Received " << stringRequest << std::endl;
        
        auto decodedRequest = split(stringRequest, ';');
        if (decodedRequest.first.empty() || decodedRequest.second.empty())
        {
            socket.send(zmq::buffer("Failed to decode message"), zmq::send_flags::none);
        }

        bool solved = false;
        for(auto& solver : solvers)
        {
	        if (solver.first == decodedRequest.first)
	        {
                std::string result;
                try
                {
                    result = solver.second->solve(decodedRequest.second);
                    solved = true;
                }
                catch(std::exception& ex)
                {
                    result.append("FAILED;");
                	result.append(ex.what());
                    solved = false;
                }
                socket.send(zmq::buffer(solver.first + ";" + result), zmq::send_flags::none);
                break;
	        }
        }

        if (!solved)
        {
            std::cout << "Failed to process: " << stringRequest << std::endl;
        }
        else
        {
            std::cout << "Result: " << solved << std::endl;
        }
    }
}

//TODO: Clean up and improve performance
std::pair<std::string, std::string> Connector::split(const std::string& input, char token)
{
    std::string first;
    std::string second;
    int size = input.size();
    int pos = 0;
    bool secondItem = false;
    while(pos < size)
    {
        if (!secondItem)
        {
            if (input[pos] == token)
            {
                secondItem = true;
            }
            else
            {
                first.push_back(input[pos]);
            }
        }
        else
        {
            second.push_back(input[pos]);
        }
        pos++;
    }

    auto result = std::make_pair(first, second);
    return result;
}

void Connector::setSolver(std::string solverId, std::unique_ptr<ISolver> solver)
{
    std::cout << "Added: " << solverId << " solver." << std::endl;
    solvers[solverId] = std::move(solver);
}