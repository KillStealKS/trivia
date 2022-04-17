#ifndef IREQUESTHANDLER_H_
#define IREQUESTHANDLER_H_

#include "JsonResoponsePacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include <chrono>
#include <vector>

using system_clock = std::chrono::system_clock;
class IRequestHandler;

typedef struct RequestInfo
{
	int requestID;
	time_t recievalTime;
	std::vector<unsigned char> buffer;
} RequestInfo;

typedef struct RequestResult
{
	std::vector<unsigned char> response;
	IRequestHandler* newHandler;
} RequestResult;

class IRequestHandler 
{
public:
	virtual bool isRequestRelevant(RequestInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo) = 0;
private:

};

#endif // !IREQUESTHANDLER_H_
