#ifndef DESIRIALIZER_H_
#define DESIRIALIZER_H_

#include "Responses.h"
#include "json.hpp"

using json = nlohmann::json;

class Deserializer {
  public:
    static ErrorResponse
    deserializeErrorResponse(std::vector<unsigned char> buffer);
    static LoginResponse
    deserializeLoginResponse(std::vector<unsigned char> buffer);
    static SignupResponse
    deserializeSignupResponse(std::vector<unsigned char> buffer);
    static LogoutResponse
    deserializeLogoutResponse(std::vector<unsigned char> buffer);
    static GetPlayersInRoomResponse
    deserializeGetPlayersInRoomResponse(std::vector<unsigned char> buffer);
    static GetRoomsResponse
    deserializeGetRoomsResponse(std::vector<unsigned char> buffer);
    static JoinRoomResponse
    deserializeJoinRoomResponse(std::vector<unsigned char> buffer);
    static CreateRoomResponse
    deserializeCreateRoomResponse(std::vector<unsigned char> buffer);
    static GetPersonalStatsResponse
    deserializePersonalStatsResponse(std::vector<unsigned char> buffer);
    static GetHighScoreResponse
    deserializeGetHighscoreResponse(std::vector<unsigned char> buffer);
    static CloseRoomResponse
    deserializeCloseRoomResponse(std::vector<unsigned char> buffer);
    static StartGameResponse
    deserializeStartGameResponse(std::vector<unsigned char> buffer);
    static GetRoomStateResponse
    deserializeGetRoomStateResponse(std::vector<unsigned char> buffer);
    static LeaveRoomResponse
    deserializeLeaveRoomResponse(std::vector<unsigned char> buffer);
    static LeaveGameResponse
    deserializeLeaveGameResponse(std::vector<unsigned char> buffer);
    static GetQuestionResponse
    deserializeGetQuestionResponse(std::vector<unsigned char> buffer);
    static SubmitAnswerResponse
    deserializeSubmitAnswerResponse(std::vector<unsigned char> buffer);
    static GetGameResultsResponse
    deserializeGetGameResultsResponse(std::vector<unsigned char> buffer);
};

#endif // !DESIRIALIZER_H_
