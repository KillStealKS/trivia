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
    RQ_HIGHSCORE
};

typedef struct LoginRequest {
    std::string username;
    std::string password;
} LoginRequest;

typedef struct SignupRequest {
    std::string username;
    std::string password;
    std::string email;
    std::string addr;
    std::string phone;
    std::string date;
} SignupRequest;

typedef struct GetPlayersInRoomRequest {
    unsigned int roomId;
} GetPlayersInRoomRequest;

typedef struct JoinRoomRequest {
    unsigned int roomId;
} JoinRoomRequest;

typedef struct CreateRoomRequest {
    std::string roomName;
    unsigned int maxUsers;
    unsigned int questionCount;
    unsigned int answerTimeout;
} CreateRoomRequest;

#endif // !REQUESTS_H_