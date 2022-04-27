#include "Server.h"
#include "JsonResponsePacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "WSAInitializer.h"
#include <iostream>
#include <string>
#include <thread>

/**
 * @brief Starts the server.
 */
void Server::run() {
    // Start connector thread
    std::thread t_connector(&Communicator::startHandleRequests,
                            &m_communicator);
    t_connector.detach();

    // Check for input
    while (true) {
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit")
            return;
    }
}

int main() {
    try {
        WSAInitializer WSAInit;
        Server server;
        server.run();
    } catch (const std::exception &e) {
        std::cout << e.what();
    }

    return 0;
}