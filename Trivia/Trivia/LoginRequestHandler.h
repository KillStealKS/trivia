#ifndef LOGINREQUESTHANDLER_H_
#define LOGINREQUESTHANDLER_H_

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class LoginManager;
class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler {
  public:
    LoginRequestHandler(RequestHandlerFactory *factory, LoginManager *manager);
    bool isRequestRelevant(RequestInfo RI) override;
    RequestResult handleRequest(RequestInfo RI) override;

  private:
    RequestHandlerFactory &m_handlerFactory;
    LoginManager &m_loginManager;
};

#endif // !LOGINREQUESTHANDLER_H_