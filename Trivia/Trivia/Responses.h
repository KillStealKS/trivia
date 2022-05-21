#ifndef RESPONSES_H_
#define RESPONSES_H_

#include "IDatabase.h"
#include "Room.h"
#include <iostream>
#include <vector>

enum responseCodes {
    RS_ERROR = -1,
    RS_LOGIN = 1,
    RS_SIGNUP,
    RS_LOGOUT,
    RS_GETROOMS,
    RS_PLAYERSINROOM,
    RS_HIGHSCORE,
    RS_PERSONALSTATS,
    RS_JOINROOM,
    RS_CREATEROOM
};

typedef struct LoginResponse {
    unsigned int status;
} LoginResponse;

typedef struct SignupResponse {
    unsigned int status;
} SignupResponse;

typedef struct LogoutResponse {
    unsigned int status;
} LogoutResponse;

typedef struct GetRoomsResponse {
    unsigned int status;
    std::vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct GetPlayersInRoomResponse {
    std::vector<std::string> players;
} GetPlayersInRoomResponse;

typedef struct GetHighScoreResponse {
    unsigned int status;
    std::vector<std::string> statistics;
} GetHighScoreResponse;

typedef struct GetPersonalStatsResponse {
    unsigned int status;
    Statistics statistics;
} GetPersonalStatsResponse;

typedef struct JoinRoomResponse {
    unsigned int status;
} JoinRoomResponse;

typedef struct CreateRoomResponse {
    unsigned int status;
} CreateRoomResponse;

typedef struct ErrorResponse {
    std::string message;
} ErrorResponse;

#endif // !RESPONSES_H_