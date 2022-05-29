#ifndef COMMUNICATOR_H_
#define COMMUNICATOR_H_

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <exception>
#include <iostream>
#include <thread>
#include <vector>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "5656"

class Communicator {
  public:
    ~Communicator();
    static Communicator communicator;

    void startNewConnection();
    std::vector<unsigned char> sendRequest(std::vector<unsigned char> request);

  private:
    SOCKET m_socket;
};

#endif // !COMMUNICATOR_H_
