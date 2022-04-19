#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo ReqInf)
{
	if (!((int)ReqInf.buffer.front() == RQ_LOGIN || (int)ReqInf.buffer.front() == RQ_SIGNUP))
		return false;
	
	return true;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInf)
{
	RequestResult reqRes;
	
	if (isRequestRelevant(reqInf))
	{
		if (reqInf.buffer.front() == RQ_SIGNUP)
		{
			SignupResponse signupRes = { RS_SIGNUP };
			reqRes.response = JsonResoponsePacketSerializer::serializeResponse(signupRes);
			reqRes.newHandler = new LoginRequestHandler;
		}
		else if (reqInf.buffer.front() == RQ_LOGIN)
		{
			LoginResponse loginRes = { RS_LOGIN };
			reqRes.response = JsonResoponsePacketSerializer::serializeResponse(loginRes);
			reqRes.newHandler = new LoginRequestHandler;
		}
	}
	else
	{
		ErrorResponse errRes = { "Illegal message code." };
		reqRes.response = JsonResoponsePacketSerializer::serializeResponse(errRes);
		reqRes.newHandler = new LoginRequestHandler;
	}

	return reqRes;
}
