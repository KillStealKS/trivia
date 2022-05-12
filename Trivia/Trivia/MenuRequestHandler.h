#ifndef MENUREQUESTHANDLER_H_
#define MENUREQUESTHANDLER_H_

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class MenuRequestHandler : public IRequestHandler {
	bool isRequestRelevant(RequestInfo RI) override;
	RequestResult handleRequest(RequestInfo RI) override;

private:
	
	//RequestHandlerFactory& m_handlerFactory;
};

#endif // !MENUREQUESTHANDLER_H_