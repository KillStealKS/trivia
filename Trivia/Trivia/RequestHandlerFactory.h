#ifndef REQUESTHANDLERFACTORY_H_
#define REQUESTHANDLERFACTORY_H_

#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include <mutex>

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory {
  public:
    RequestHandlerFactory();

    IDatabase *getDatabase() const { return m_database; }

    LoginRequestHandler *createLoginRequestHandler();
    MenuRequestHandler *createMenuRequestHandler();

  private:
    IDatabase *m_database;
    LoginManager m_loginManager;
};

#endif // !REQUESTHANDLERFACTORY_H_