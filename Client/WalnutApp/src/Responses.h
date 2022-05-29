#ifndef RESPONSES_H_
#define RESPONSES_H_

#include <iostream>
#include <vector>

typedef struct Statistics {
    std::string username;
    int totalGames;
    int gamesWon;
    int totalAnswers;
    int correctAnswers;
    int totalAnswerTime;
    int highscore;
} Statistics;

typedef struct RoomData {
    unsigned int id;
    std::string name;
    unsigned int maxPlayers;
    unsigned int numOfQuestions;
    unsigned int timePerQuestion;
    unsigned int isActive;
} RoomData;

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
};

typedef struct ErrorResponse {
    std::string message;
} ErrorResponse;

typedef struct LoginResponse {
    unsigned int status;
} LoginResponse;

typedef struct SignupResponse {
    unsigned int status;
} SignupResponse;

typedef struct LogoutResponse {
    unsigned int status;
} LogoutResponse;

typedef struct GetPlayersInRoomResponse {
    std::vector<std::string> players;
} GetPlayersInRoomResponse;

typedef struct GetRoomsResponse {
    unsigned int status;
    std::vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct JoinRoomResponse {
    unsigned int status;
} JoinRoomResponse;

typedef struct CreateRoomResponse {
    unsigned int status;
} CreateRoomResponse;

typedef struct GetPersonalStatsResponse {
    unsigned int status;
    Statistics statistics;
} GetPersonalStatsResponse;

typedef struct GetHighScoreResponse {
    unsigned int status;
    std::vector<std::string> statistics;
} GetHighScoreResponse;

typedef struct CloseRoomResponse {
    unsigned int status;
} CloseRoomResponse;

typedef struct StartGameResponse {
    unsigned int status;
};

typedef struct GetRoomStateResponse {
    unsigned int status;
    bool hasGameBegun;
    std::vector<std::string> players;
    unsigned int questionCount;
    unsigned int answerTimeout;
} GetRoomStateResponse;

typedef struct LeaveRoomResponse {
    unsigned int status;
};

#endif // !RESPONSES_H_
