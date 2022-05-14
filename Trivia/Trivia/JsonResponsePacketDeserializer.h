#pragma once

#include "Requests.h"
#include "json.hpp"
#include <vector>

using json = nlohmann::json;

class JsonResponsePacketDeserializer {
  public:
    static LoginRequest
    deserializeLoginRequest(std::vector<unsigned char> buffer);
    static SignupRequest
    deserializeSignupRequest(std::vector<unsigned char> buffer);

  private:
};