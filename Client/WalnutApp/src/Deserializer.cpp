#include "Deserializer.h"

/**
 * @brief Deserialize error response.
 *
 * @param buffer Serialized response.
 * @return ErrorResponse Deserialized response
 */
ErrorResponse
Deserializer::deserializeErrorResponse(std::vector<unsigned char> buffer) {
    ErrorResponse newErrorResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newErrorResponse.message = msg["message"];

    return newErrorResponse;
}

/**
 * @brief Deserialize login response.
 *
 * @param buffer Serialized response.
 * @return LoginResponse Deserialized response
 */
LoginResponse
Deserializer::deserializeLoginResponse(std::vector<unsigned char> buffer) {
    LoginResponse newLoginResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    try {
        json msg = json::from_ubjson(buffer);
        newLoginResponse.status = msg["status"];
    } catch (const std::exception &e) {
        std::cout << e.what();
    }

    return newLoginResponse;
}

/**
 * @brief Deserialize signup response.
 *
 * @param buffer Serialized response.
 * @return SignupResponse Deserialized response
 */
SignupResponse
Deserializer::deserializeSignupResponse(std::vector<unsigned char> buffer) {
    SignupResponse newSignupResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newSignupResponse.status = msg["status"];

    return newSignupResponse;
}

/**
 * @brief Deserialize logout response.
 *
 * @param buffer Serialized response.
 * @return LogoutResponse Deserialized response
 */
LogoutResponse
Deserializer::deserializeLogoutResponse(std::vector<unsigned char> buffer) {
    LogoutResponse newLogoutResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newLogoutResponse.status = msg["status"];

    return newLogoutResponse;
}

/**
 * @brief Deserialize getPlayersInRoom response.
 *
 * @param buffer Serialized response.
 * @return GetPlayersInRoomResponse Deserialized response
 */
GetPlayersInRoomResponse Deserializer::deserializeGetPlayersInRoomResponse(
    std::vector<unsigned char> buffer) {
    GetPlayersInRoomResponse newGetPlayersResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    for (auto i : msg["playersInRoom"]) {
        newGetPlayersResponse.players.push_back(i);
    }

    return newGetPlayersResponse;
}

/**
 * @brief Deserialize getRooms response.
 *
 * @param buffer Serialized response.
 * @return GetRoomsResponse Deserialized response
 */
GetRoomsResponse
Deserializer::deserializeGetRoomsResponse(std::vector<unsigned char> buffer) {
    GetRoomsResponse newGetRoomsResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newGetRoomsResponse.status = msg["status"];
    for (json i : msg["rooms"]) {
        RoomData data;
        data.id = i["roomID"];
        data.name = i["name"];
        data.maxPlayers = i["maxPlayers"];
        data.numOfQuestions = i["numOfQuestions"];
        data.timePerQuestion = i["timePerQuestion"];
        data.isActive = i["isActive"];
        newGetRoomsResponse.rooms.push_back(data);
    }

    return newGetRoomsResponse;
}

/**
 * @brief Deserialize joinRoom response.
 *
 * @param buffer Serialized response.
 * @return JoinRoomResponse Deserialized response
 */
JoinRoomResponse
Deserializer::deserializeJoinRoomResponse(std::vector<unsigned char> buffer) {
    JoinRoomResponse newJoinRoomResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newJoinRoomResponse.status = msg["status"];

    return newJoinRoomResponse;
}

/**
 * @brief Deserialize createRoom response.
 *
 * @param buffer Serialized response.
 * @return CreateRoomResponse Deserialized response
 */
CreateRoomResponse
Deserializer::deserializeCreateRoomResponse(std::vector<unsigned char> buffer) {
    CreateRoomResponse newCreateRoomResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newCreateRoomResponse.status = msg["status"];

    return newCreateRoomResponse;
}

/**
 * @brief Deserialize getPersonalStats response.
 *
 * @param buffer Serialized response.
 * @return GetPersonalStatsResponse Deserialized response
 */
GetPersonalStatsResponse Deserializer::deserializePersonalStatsResponse(
    std::vector<unsigned char> buffer) {
    GetPersonalStatsResponse newGetStatsResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newGetStatsResponse.status = msg["status"];
    newGetStatsResponse.statistics.totalGames = msg["statistics"]["totalGames"];
    newGetStatsResponse.statistics.gamesWon = msg["statistics"]["gamesWon"];
    newGetStatsResponse.statistics.totalAnswers =
        msg["statistics"]["totalAnswers"];
    newGetStatsResponse.statistics.correctAnswers =
        msg["statistics"]["correctAnswers"];
    newGetStatsResponse.statistics.totalAnswerTime =
        msg["statistics"]["totalAnswerTime"];
    newGetStatsResponse.statistics.highscore = msg["statistics"]["highscore"];

    return newGetStatsResponse;
}

/**
 * @brief Deserialize getHighScore response.
 *
 * @param buffer Serialized response.
 * @return GetHighScoreResponse Deserialized response
 */
GetHighScoreResponse Deserializer::deserializeGetHighscoreResponse(
    std::vector<unsigned char> buffer) {
    GetHighScoreResponse newGetHighscoreResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newGetHighscoreResponse.status = msg["status"];
    for (auto i : msg["statistics"]) {
        newGetHighscoreResponse.statistics.push_back(i);
    }

    return newGetHighscoreResponse;
}

/**
 * @brief Deserialize closeRoom response.
 *
 * @param buffer Serialized response.
 * @return CloseRoomResponse Deserialized response
 */
CloseRoomResponse
Deserializer::deserializeCloseRoomResponse(std::vector<unsigned char> buffer) {
    CloseRoomResponse newCloseRoomResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newCloseRoomResponse.status = msg["status"];

    return newCloseRoomResponse;
}

/**
 * @brief Deserialize startGame response.
 *
 * @param buffer Serialized response.
 * @return StartGameResponse Deserialized response
 */
StartGameResponse
Deserializer::deserializeStartGameResponse(std::vector<unsigned char> buffer) {
    StartGameResponse newStartGameResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newStartGameResponse.status = msg["status"];

    return newStartGameResponse;
}

/**
 * @brief Deserialize getRoomState response.
 *
 * @param buffer Serialized response.
 * @return GetRoomStateResponse Deserialized response
 */
GetRoomStateResponse Deserializer::deserializeGetRoomStateResponse(
    std::vector<unsigned char> buffer) {
    GetRoomStateResponse newGetRoomStateResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newGetRoomStateResponse.status = msg["status"];
    newGetRoomStateResponse.hasGameBegun = msg["hasGameBegun"];
    for (auto i : msg["players"])
        newGetRoomStateResponse.players.push_back(i);
    newGetRoomStateResponse.questionCount = msg["questionCount"];
    newGetRoomStateResponse.answerTimeout = msg["answerTimeout"];

    return newGetRoomStateResponse;
}

/**
 * @brief Deserialize leaveRoom response.
 *
 * @param buffer Serialized response.
 * @return LeaveRoomResponse Deserialized response
 */
LeaveRoomResponse
Deserializer::deserializeLeaveRoomResponse(std::vector<unsigned char> buffer) {
    LeaveRoomResponse newLeaveRoomResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newLeaveRoomResponse.status = msg["status"];

    return newLeaveRoomResponse;
}

/**
 * @brief Deserialize leaveGame response.
 *
 * @param buffer Serialized response.
 * @return leaveGameResponse Deserialized response
 */
LeaveGameResponse
Deserializer::deserializeLeaveGameResponse(std::vector<unsigned char> buffer) {
    LeaveGameResponse newLeaveGameResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newLeaveGameResponse.status = msg["status"];

    return newLeaveGameResponse;
}

/**
 * @brief Deserialize getQuestion response.
 *
 * @param buffer Serialized response.
 * @return getQuestionResponse Deserialized response
 */
GetQuestionResponse Deserializer::deserializeGetQuestionResponse(
    std::vector<unsigned char> buffer) {
    GetQuestionResponse newGetQuestionResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newGetQuestionResponse.status = msg["status"];
    newGetQuestionResponse.question = msg["question"];
    newGetQuestionResponse.answers = msg["answers"];

    return newGetQuestionResponse;
}

/**
 * @brief Deserialize submitAnswer response.
 *
 * @param buffer Serialized response.
 * @return submitAnswerResponse Deserialized response
 */
SubmitAnswerResponse Deserializer::deserializeSubmitAnswerResponse(
    std::vector<unsigned char> buffer) {
    SubmitAnswerResponse newSubmitAnswerResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newSubmitAnswerResponse.status = msg["status"];

    return newSubmitAnswerResponse;
}

/**
 * @brief Deserialize getGameResults response.
 *
 * @param buffer Serialized response.
 * @return getGameResultsResponse Deserialized response
 */
GetGameResultsResponse Deserializer::deserializeGetGameResultsResponse(
    std::vector<unsigned char> buffer) {
    GetGameResultsResponse newGetGameResultsResponse;

    // code
    int code = buffer.front();
    buffer.erase(buffer.begin());

    // length
    unsigned char len[4];
    for (int i = 0; i < 4; i++) {
        len[i] = buffer.front();
        buffer.erase(buffer.begin());
    }

    long int intLen;
    memcpy(&intLen, len, sizeof(intLen));

    // message
    json msg = json::from_ubjson(buffer);

    newGetGameResultsResponse.status = msg["status"];
    for (auto i : msg["results"]) {
        PlayerResults results;
        results.username = i["username"];
        results.correctAnswerCount = i["correctAnswerCount"];
        results.wrongAnswerCount = i["wrongAnswerCount"];
        results.averageAnswerTime = i["averageAnswerTime"];

        newGetGameResultsResponse.results.push_back(results);
    }

    return newGetGameResultsResponse;
}
