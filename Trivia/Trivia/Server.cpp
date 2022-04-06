#include "Server.h"
#include "WSAInitializer.h"
#include <iostream>
#include <string>
#include <thread>

void Server::run() {
    std::thread t_connector(&Communicator::startHandleRequests,
                            &m_communicator);
    t_connector.detach();

    while (true) {
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit")
            return;
    }
}

void main() 
{
    try
    {
        WSAInitializer WSAInit;
        Server server;
        server.run();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }
}