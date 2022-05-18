#include "Server.h"
#include "JsonResponsePacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include <iostream>
#include <string>
#include <thread>

Server::Server() : m_communicator(Communicator(m_handlerFactory)), m_database(new SQLiteDatabase()) {
    m_handlerFactory = RequestHandlerFactory();
    Communicator m_communicator(m_handlerFactory);
    m_database->open();
}

/**
 * @brief Construct a new Server::Server object
 */
Server::Server()
    : m_handlerFactory(), m_communicator(m_handlerFactory),
      m_database(m_handlerFactory.getDatabase()) {}

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