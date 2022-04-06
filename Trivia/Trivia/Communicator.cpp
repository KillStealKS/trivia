#include "Communicator.h"
#include "LoginRequestHandler.h"
#include "WSAInitializer.h"
#include <exception>
#include <iostream>
#include <string>
#include <thread>

Communicator::Communicator() {
    m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (m_serverSocket == INVALID_SOCKET)
        throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator() {
    try {
        closesocket(m_serverSocket);
    } catch (...) {
    }
}

void Communicator::startHandleRequests() {
    try {
        struct sockaddr_in sa = {0};

        sa.sin_port = htons(PORT);
        sa.sin_family = AF_INET;
        sa.sin_addr.s_addr = INADDR_ANY;

        if (bind(m_serverSocket, (struct sockaddr *)&sa, sizeof(sa)) == SOCKET_ERROR)
            throw std::exception(__FUNCTION__ " - bind");

        if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
            throw std::exception(__FUNCTION__ " - listen");
        std::cout << "Listening on port " << PORT << std::endl;

        while (true) {
            bindAndListen();
        }
    }
    catch (std::exception& e)
    {
        std::cout << "Error occured : " << e.what() << std::endl;
        closesocket(m_serverSocket);
    }
}

void Communicator::bindAndListen() {
    SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
    if (client_socket == INVALID_SOCKET)
        throw std::exception(__FUNCTION__);

    std::cout << "Client accepted." << std::endl;

    std::thread t(&Communicator::handleNewClient, this, client_socket);
    t.detach();
}

void Communicator::handleNewClient(SOCKET clientSocket) {
    // TODO: mutex

    m_clients.insert({clientSocket, new LoginRequestHandler});
    std::cout << "client inserted\n";

    while (true)
    {
        char* data = new char[20];
        for (int i = 0; i < 20; i++)
            data[i] = ' ';
        
        if (recv(clientSocket, data, 20, 0) == INVALID_SOCKET)
        {
            std::cout << std::to_string(WSAGetLastError());
        }
        else
        {
            std::cout << std::string(data) << std::endl;
            send(clientSocket, data, 20, 0);
        }
        delete[] data;
    }
}
