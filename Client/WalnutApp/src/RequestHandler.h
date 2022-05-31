#ifndef REQUESTHANDLER_H_
#define REQUESTHANDLER_H_

#include "Communicator.h"
#include "Deserializer.h"
#include "Requests.h"
#include "Responses.h"
#include "Serializer.h"
#include <regex>

class RequestHandler {
  public:
    static LoginResponse loginRequest(std::string username,
                                      std::string password);
    static SignupResponse signupRequest(std::string username,
                                        std::string password, std::string email,
                                        std::string addr, std::string phone,
                                        std::string date);
    static LogoutResponse logoutRequest();
    static GetPlayersInRoomResponse
    getPlayersInRoomRequest(unsigned int roomId);
    static GetRoomsResponse getRoomsRequest();
    static JoinRoomResponse joinRoomRequest(unsigned int roomId);
    static CreateRoomResponse createRoomRequest(std::string roomName,
                                                unsigned int maxUsers,
                                                unsigned int questionCount,
                                                unsigned int answerTimeout);
    static GetPersonalStatsResponse getPersonalStatsRequest();
    static GetHighScoreResponse getHighscoreRequest();
    static CloseRoomResponse closeRoomRequest();
    static StartGameResponse startGameRequest();
    static GetRoomStateResponse getRoomStateRequest();
    static LeaveRoomResponse leaveRoomRequest();
    static LeaveGameResponse leaveGameRequest();
    static GetQuestionResponse getQuestionRequest();
    static SubmitAnswerResponse submitAnswerRequest(unsigned int answerId);
    static GetGameResultsResponse getGameResultsRequest();
};

#endif // !REQUESTHANDLER_H_
