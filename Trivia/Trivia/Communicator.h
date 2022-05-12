#ifndef COMMUNICATOR_H_
#define COMMUNICATOR_H_

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include <WinSock2.h>
#include <map>

#define PORT 5656

class Communicator {
  public:
    Communicator(RequestHandlerFactory& factory);
    ~Communicator();

    void startHandleRequests();

  private:
    SOCKET m_serverSocket;
    std::map<SOCKET, IRequestHandler *> m_clients;
    RequestHandlerFactory& m_handlerFactory;
    static int m_idCounter;

    void bindAndListen();
    void handleNewClient(SOCKET clientSocket);
};

#endif // !COMMUNICATOR_H_