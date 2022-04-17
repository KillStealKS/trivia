#include "JsonResponsePacketSerializer.h"

std::vector<unsigned char> JsonResoponsePacketSerializer::serializeResponse(ErrorResponse errorResponse)
{
	std::vector<unsigned char> buffer;
	json responseJson = json::object();
	responseJson["message"] = errorResponse.message;

	//code
	buffer.push_back((unsigned char)RS_ERROR);

	//length
	unsigned char len[4];
	long int intLen = sizeof(responseJson);
	memcpy(len, &intLen, sizeof(intLen));
	for (int i = 0; i < 4; i += sizeof(unsigned char))
	{
		buffer.push_back(len[i]);
	}

	//message
	std::vector<unsigned char> msg = json::to_ubjson(responseJson);
	buffer.insert(buffer.end(), msg.begin(), msg.end());

	return buffer;
}

std::vector<unsigned char> JsonResoponsePacketSerializer::serializeResponse(LoginResponse loginResponse)
{
	std::vector<unsigned char> buffer;
	json responseJson = json::object();
	responseJson["status"] = loginResponse.status;

	//code
	buffer.push_back((unsigned char)RS_LOGIN);

	//length
	unsigned char len[4];
	long int intLen = sizeof(responseJson);
	memcpy(len, &intLen, sizeof(intLen));
	for (int i = 0; i < 4; i += sizeof(unsigned char))
	{
		buffer.push_back(len[i]);
	}

	//message
	std::vector<unsigned char> msg = json::to_ubjson(responseJson);
	buffer.insert(buffer.end(), msg.begin(), msg.end());

	return buffer;
}

std::vector<unsigned char> JsonResoponsePacketSerializer::serializeResponse(SignupResponse signupResponse)
{
	std::vector<unsigned char> buffer;
	json responseJson = json::object();
	responseJson["status"] = signupResponse.status;

	//code
	buffer.push_back((unsigned char)RS_SIGNUP);

	//length
	unsigned char len[4];
	long int intLen = sizeof(responseJson);
	
	memcpy(len, &intLen, sizeof(intLen));
	for (int i = 0; i < 4; i += sizeof(unsigned char))
		buffer.push_back(len[i]);

	//message
	std::vector<unsigned char> msg = json::to_ubjson(responseJson);
	buffer.insert(buffer.end(), msg.begin(), msg.end());

	return buffer;
}
