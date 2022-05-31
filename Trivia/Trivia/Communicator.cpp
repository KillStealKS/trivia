#include "Communicator.h"
#include "JsonResponsePacketDeserializer.h"
#include "LoginRequestHandler.h"
#include "WSAInitializer.h"
#include <exception>
#include <iostream>
#include <string>
#include <thread>

// Initialize counter.
int Communicator::m_idCounter = 1;

/**
 * @brief Construct a new Communicator:: Communicator object.
 */
Communicator::Communicator(RequestHandlerFactory &factory)
    : m_handlerFactory(factory) {
    // Create new socket.
    m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (m_serverSocket == INVALID_SOCKET)
        throw std::exception(__FUNCTION__ " - socket");
}

/**
 * @brief Destroy the Communicator:: Communicator object.
 */
Communicator::~Communicator() {
    try {
        closesocket(m_serverSocket);
    } catch (...) {
    }
}

/**
 * @brief Starts connection requests handling.
 */
void Communicator::startHandleRequests() {
    try {
        // Start listening.
        struct sockaddr_in sa = {0};

        sa.sin_port = htons(PORT);
        sa.sin_family = AF_INET;
        sa.sin_addr.s_addr = INADDR_ANY;

        if (bind(m_serverSocket, (struct sockaddr *)&sa, sizeof(sa)) ==
            SOCKET_ERROR)
            throw std::exception(__FUNCTION__ " - bind");

        if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
            throw std::exception(__FUNCTION__ " - listen");
        std::cout << "Listening on port " << PORT << std::endl;

        while (true) {
            bindAndListen();
        }
    } catch (std::exception &e) {
        std::cout << "Error occurred : " << e.what() << std::endl;
        closesocket(m_serverSocket);
    }
}

/**
 * @brief Listens for new clients and binds them.
 */
void Communicator::bindAndListen() {
    SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
    if (client_socket == INVALID_SOCKET)
        throw std::exception(__FUNCTION__ " - bind new client socket");

    std::cout << "Client accepted." << std::endl;

    // Start handling thread.
    std::thread t(&Communicator::handleNewClient, this, client_socket);
    t.detach();
}

/**
 * @brief Handles clients.
 *
 * @param clientSocket Client socket.
 */
void Communicator::handleNewClient(SOCKET clientSocket) {
    // Add client to map.
    m_clients.insert(
        {clientSocket, m_handlerFactory.createLoginRequestHandler()});
    std::cout << "client inserted\n";

    while (true) {
        char buffer[1024];
        std::vector<unsigned char> request;
        
        // Get request from client.
        int result = recv(clientSocket, buffer, 1024, 0);
        if (result == SOCKET_ERROR)
            std::cout << std::to_string(WSAGetLastError());
        else if (result == 0) { //socket closed
            delete m_clients[clientSocket];
            m_clients.erase(clientSocket);
            closesocket(clientSocket);
            break;
        }
        else { // Request received successfully.
            for (int i = 0; i < result; i++)
                request.push_back(buffer[i]);
            
            // Process request.
            RequestInfo reqInf = {m_idCounter++,
                                  system_clock::to_time_t(system_clock::now()),
                                  request};
            
            std::cout << "Processing request number " + std::to_string(reqInf.requestID) 
                + ", code: " + std::to_string(request[0]) << std::endl;
            
            RequestResult reqRes =
                m_clients[clientSocket]->handleRequest(reqInf);

            // Create new request handler for socket.
            if (reqRes.newHandler != nullptr) {
                delete m_clients[clientSocket];
                m_clients[clientSocket] = reqRes.newHandler;
            }

            // Send response to client.
            for (int i = 0; i < reqRes.response.size(); i++)
                buffer[i] = reqRes.response[i];

            send(clientSocket, buffer, reqRes.response.size(), 0);
        }
    }
}
