#ifndef SERVER_H_
#define SERVER_H_

#include "Communicator.h"

class Server {
  public:
    void run();

  private:
    Communicator m_communicator;
};

#endif // !SERVER_H_