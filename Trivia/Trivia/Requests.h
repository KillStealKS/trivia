#ifndef REQUESTS_H_
#define REQUESTS_H_

#include <iostream>

enum requestCodes {
    RQ_LOGIN = 1,
    RQ_SIGNUP,
    RQ_LOGOUT,
    RQ_GETPLAYERS,
    RQ_GETROOM,
    RQ_JOINROOM,
    RQ_CREATEROOM,
    RQ_PERSONALSTATS,
    RQ_HIGHSCORE,
    RQ_CLOSEROOM,
    RQ_STARTGAME,
    RQ_GETROOMSTATE,
    RQ_LEAVEROOM,
    RQ_LEAVEGAME,
    RQ_GETQUESTION,
    RQ_SUBMITANSWER,
    RQ_GETGAMERESULTS,
};

struct LoginRequest {
    std::string username;
    std::string password;
};

struct SignupRequest {
    std::string username;
    std::string password;
    std::string email;
    std::string addr;
    std::string phone;
    std::string date;
};

struct GetPlayersInRoomRequest {
    unsigned int roomId;
};

struct JoinRoomRequest {
    unsigned int roomId;
};

struct CreateRoomRequest {
    std::string roomName;
    unsigned int maxUsers;
    unsigned int questionCount;
    unsigned int answerTimeout;
};

struct SubmitAnswerRequest {
    unsigned int answerId;
    float timeToAnswer;
};

#endif // !REQUESTS_H_