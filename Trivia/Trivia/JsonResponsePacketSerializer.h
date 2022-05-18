#pragma once

#include "Responses.h"
#include "json.hpp"
#include <iostream>
#include <vector>

using json = nlohmann::json;

class JsonResponsePacketSerializer {
  public:
    static std::vector<unsigned char> serializeResponse(ErrorResponse e);
    static std::vector<unsigned char> serializeResponse(LoginResponse l);
    static std::vector<unsigned char> serializeResponse(SignupResponse s);

  private:
};