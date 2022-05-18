#ifndef SERVER_H_
#define SERVER_H_

#include "Communicator.h"
#include "RequestHandlerFactory.h"

class Server {
  public:
    Server();
    void run();

  private:
    RequestHandlerFactory m_handlerFactory;
    IDatabase *m_database;
    Communicator m_communicator;
    IDatabase* m_database;
    RequestHandlerFactory m_handlerFactory;
};

#endif // !SERVER_H_