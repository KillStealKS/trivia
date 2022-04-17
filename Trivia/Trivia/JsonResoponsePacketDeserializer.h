#pragma once

#include "Requests.h"
#include "json.hpp"
#include <vector>

using json = nlohmann::json;

class JsonResoponsePacketDeserializer
{
public:
	LoginRequest deserelizeLoginRequest(std::vector<unsigned char> buffer);
	SignupRequest deserelizeSignupRequest(std::vector<unsigned char> buffer);
private:

};