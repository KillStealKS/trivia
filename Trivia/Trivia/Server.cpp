#include "Server.h"
#include "WSAInitializer.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonResoponsePacketDeserializer.h"
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

int main() 
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

    return 0;
}