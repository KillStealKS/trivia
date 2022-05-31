#include "Communicator.h"

Communicator Communicator::communicator = Communicator();

/**
 * @brief Destroy the Communicator::Communicator object.
 */
Communicator::~Communicator() {
    try {
        int iResult = shutdown(m_socket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            closesocket(m_socket);
            WSACleanup();
            throw std::exception(__FUNCTION__ " - shutdown failed: %d\n",
                                 WSAGetLastError());
        }
        closesocket(m_socket);
        WSACleanup();
    } catch (...) {
    }
}

/**
 * @brief Starts a new connection with the server.
 */
void Communicator::startNewConnection() {
    try {
        WSADATA wsaData;
        struct addrinfo *result = NULL, *ptr = NULL, hints;
        int iResult;

        // Initialize Winsock
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0)
            throw std::exception(
                __FUNCTION__ " - WSAStartup failed with error: %d\n", iResult);

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        // Resolve the server address and port
        iResult = getaddrinfo(SERVER_IP, SERVER_PORT, &hints, &result);
        if (iResult != 0) {
            WSACleanup();
            throw std::exception(
                __FUNCTION__ " - getaddrinfo failed with error: %d\n", iResult);
        }

        // Attempt to connect to an address until one succeeds
        for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
            // Create a SOCKET for connecting to server
            m_socket =
                socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
            if (m_socket == INVALID_SOCKET) {
                WSACleanup();
                throw std::exception(
                    __FUNCTION__ " - socket failed with error: %ld\n",
                    WSAGetLastError());
            }

            // Connect to server.
            iResult = connect(m_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
            if (iResult == SOCKET_ERROR) {
                closesocket(m_socket);
                m_socket = INVALID_SOCKET;
                continue;
            }
            break;
        }

        freeaddrinfo(result);

        if (m_socket == INVALID_SOCKET) {
            WSACleanup();
            throw std::exception(
                __FUNCTION__ " - Unable to connect to server!\n");
        }
    } catch (std::exception &e) {
        std::cout << "Error occurred : " << e.what() << std::endl;
        closesocket(m_socket);
    }
}

/**
 * @brief Sends a request to the server.
 *
 * @param request Request to send.
 * @returns std::vector<unsigned char> Response.
 */
std::vector<unsigned char>
Communicator::sendRequest(std::vector<unsigned char> request) {
    char buffer[2048];
    int buflen = 2048;
    int iResult;

    // Parse request
    for (int i = 0; i < request.size(); i++)
        buffer[i] = request[i];

    // Send request
    iResult = send(m_socket, buffer, request.size(), 0);
    if (iResult == SOCKET_ERROR) {
        closesocket(m_socket);
        WSACleanup();
        throw std::exception(__FUNCTION__ " - send failed with error: %d\n",
                             WSAGetLastError());
    }

    // Recieve response
    iResult = recv(m_socket, buffer, buflen, 0);
    if (iResult == SOCKET_ERROR) {
        closesocket(m_socket);
        WSACleanup();
        throw std::exception(__FUNCTION__ " - recieve failed with error: %d\n",
                             WSAGetLastError());
    }

    // Parse response
    std::vector<unsigned char> response;
    for (int i = 0; i < iResult; i++) {
        response.push_back(buffer[i]);
    }
    return response;
}
