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
    static std::vector<unsigned char> serializeResponse(LogoutResponse l);
    static std::vector<unsigned char> serializeResponse(GetRoomsResponse gr);
    static std::vector<unsigned char>
    serializeResponse(GetPlayersInRoomResponse gp);
    static std::vector<unsigned char> serializeResponse(JoinRoomResponse jr);
    static std::vector<unsigned char> serializeResponse(CreateRoomResponse cr);
    static std::vector<unsigned char>
    serializeResponse(GetPersonalStatsResponse gs);

  private:
};