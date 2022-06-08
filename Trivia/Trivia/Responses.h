#ifndef RESPONSES_H_
#define RESPONSES_H_

#include "IDatabase.h"
#include "Room.h"
#include <iostream>
#include <map>
#include <vector>

enum responseCodes {
    RS_ERROR = 255,
    RS_LOGIN = 1,
    RS_SIGNUP,
    RS_LOGOUT,
    RS_GETPLAYERS,
    RS_GETROOMS,
    RS_JOINROOM,
    RS_CREATEROOM,
    RS_PERSONALSTATS,
    RS_HIGHSCORE,
    RS_CLOSEROOM,
    RS_STARTGAME,
    RS_GETROOMSTATE,
    RS_LEAVEROOM,
    RS_LEAVEGAME,
    RS_GETQUESTION,
    RS_SUBMITANSWER,
    RS_GETGAMERESULTS,
};

struct PlayerResults {
    std::string username;
    unsigned int correctAnswerCount;
    unsigned int wrongAnswerCount;
    unsigned int averageAnswerTime;
};

struct ErrorResponse {
    std::string message;
};

struct LoginResponse {
    unsigned int status;
};

struct SignupResponse {
    unsigned int status;
};

struct LogoutResponse {
    unsigned int status;
};

struct GetPlayersInRoomResponse {
    std::vector<std::string> players;
};

struct JoinRoomResponse {
    unsigned int status;
};

struct CreateRoomResponse {
    unsigned int status;
};

struct GetRoomsResponse {
    unsigned int status;
    std::vector<RoomData> rooms;
};

struct GetPersonalStatsResponse {
    unsigned int status;
    Statistics statistics;
};

struct GetHighScoreResponse {
    unsigned int status;
    std::vector<std::string> statistics;
};

struct CloseRoomResponse {
    unsigned int status;
};

struct StartGameResponse {
    unsigned int status;
};

struct GetRoomStateResponse {
    unsigned int status;
    bool hasGameBegun;
    std::vector<std::string> players;
    unsigned int questionCount;
    unsigned int answerTimeout;
};

struct LeaveRoomResponse {
    unsigned int status;
};

struct LeaveGameResponse {
    unsigned int status;
};

struct GetQuestionResponse {
    unsigned int status;
    std::string question;
    std::map<unsigned int, std::string> answers;
};

struct SubmitAnswerResponse {
    unsigned int status;
    unsigned int correctAnswer;
};

struct GetGameResultsResponse {
    unsigned int status;
    std::vector<PlayerResults> results;
};

#endif // !RESPONSES_H_