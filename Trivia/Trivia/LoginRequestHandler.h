#ifndef LOGINREQUESTHANDLER_H_
#define LOGINREQUESTHANDLER_H_

#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler {
    bool isRequestRelevant(RequestInfo RI) override;
    RequestResult handleRequest(RequestInfo RI) override;
};

#endif // !LOGINREQUESTHANDLER_H_