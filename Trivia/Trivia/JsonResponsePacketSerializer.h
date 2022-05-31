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
    static std::vector<unsigned char>
    serializeResponse(GetHighScoreResponse ghs);
    static std::vector<unsigned char> serializeResponse(CloseRoomResponse cr);
    static std::vector<unsigned char> serializeResponse(StartGameResponse sg);
    static std::vector<unsigned char>
    serializeResponse(GetRoomStateResponse grs);
    static std::vector<unsigned char> serializeResponse(LeaveRoomResponse lr);
    static std::vector<unsigned char> serializeResponse(LeaveGameResponse lg);
    static std::vector<unsigned char> serializeResponse(GetQuestionResponse gq);
    static std::vector<unsigned char> serializeResponse(SubmitAnswerResponse sa);
    static std::vector<unsigned char> serializeResponse(GetGameResultsResponse gr);

  private:
};