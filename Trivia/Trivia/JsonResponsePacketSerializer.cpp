#include "JsonResponsePacketSerializer.h"

/**
 * @brief Serializes error respone.
 *
 * @param errorResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char>
JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["message"] = errorResponse.message;

    // Code
    buffer.push_back((unsigned char)RS_ERROR);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);
    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char)) {
        buffer.push_back(len[i]);
    }

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes login respone.
 *
 * @param loginResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char>
JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = loginResponse.status;

    // Code
    buffer.push_back((unsigned char)RS_LOGIN);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);
    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char)) {
        buffer.push_back(len[i]);
    }

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes signup respone.
 *
 * @param signupResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char>
JsonResponsePacketSerializer::serializeResponse(SignupResponse signupResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = signupResponse.status;

    // Code
    buffer.push_back((unsigned char)RS_SIGNUP);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes logout respone.
 *
 * @param logoutResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char>
JsonResponsePacketSerializer::serializeResponse(LogoutResponse logoutResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = logoutResponse.status;

    // Code
    buffer.push_back((unsigned char)RS_LOGOUT);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes getRooms respone.
 *
 * @param getRoomsResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(
    GetRoomsResponse getRoomResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = getRoomResponse.status;
    responseJson["rooms"] = json::array();

    for (auto r : getRoomResponse.rooms) {
        json roomJson = json::object();
        roomJson["roomID"] = r.id;
        roomJson["name"] = r.name;
        roomJson["maxPlayers"] = r.maxPlayers;
        roomJson["numOfQuestions"] = r.numOfQuestions;
        roomJson["timePerQuestion"] = r.timePerQuestion;
        roomJson["isActive"] = r.isActive;

        responseJson["rooms"].insert(responseJson["rooms"].end(), roomJson);
    }

    // Code
    buffer.push_back((unsigned char)RS_GETROOMS);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes getPlayers respone.
 *
 * @param getPlayersResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(
    GetPlayersInRoomResponse getPlayersResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["playersInRoom"] = getPlayersResponse.players;

    // Code
    buffer.push_back((unsigned char)RS_GETPLAYERS);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes joinRoom respone.
 *
 * @param joinRoomResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(
    JoinRoomResponse joinRoomResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = joinRoomResponse.status;

    // Code
    buffer.push_back((unsigned char)RS_JOINROOM);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes createRoom respone.
 *
 * @param createRoomResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(
    CreateRoomResponse createRoomResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = createRoomResponse.status;

    // Code
    buffer.push_back((unsigned char)RS_CREATEROOM);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes getPersonalStats respone.
 *
 * @param getStatsResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(
    GetPersonalStatsResponse getStatsResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = getStatsResponse.status;
    responseJson["statistics"]["totalGames"] =
        getStatsResponse.statistics.totalGames;
    responseJson["statistics"]["gamesWon"] =
        getStatsResponse.statistics.gamesWon;
    responseJson["statistics"]["totalAnswers"] =
        getStatsResponse.statistics.totalAnswers;
    responseJson["statistics"]["correctAnswers"] =
        getStatsResponse.statistics.correctAnswers;
    responseJson["statistics"]["totalAnswerTime"] =
        getStatsResponse.statistics.totalAnswerTime;
    responseJson["statistics"]["highscore"] =
        getStatsResponse.statistics.highscore;

    // Code
    buffer.push_back((unsigned char)RS_PERSONALSTATS);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes getHighscore respone.
 *
 * @param getHighscoreResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(
    GetHighScoreResponse getHighscoreResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = getHighscoreResponse.status;
    responseJson["statistics"] = getHighscoreResponse.statistics;

    // Code
    buffer.push_back((unsigned char)RS_HIGHSCORE);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes closeRoom respone.
 *
 * @param closeRoomResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(
    CloseRoomResponse closeRoomResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = closeRoomResponse.status;

    // Code
    buffer.push_back((unsigned char)RS_CLOSEROOM);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes startGame respone.
 *
 * @param startGameResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(
    StartGameResponse startGameResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = startGameResponse.status;

    // Code
    buffer.push_back((unsigned char)RS_STARTGAME);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes getRoomState respone.
 *
 * @param getRoomStateResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(
    GetRoomStateResponse getRoomStateResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = getRoomStateResponse.status;
    responseJson["hasGameBegun"] = getRoomStateResponse.hasGameBegun;
    responseJson["players"] = getRoomStateResponse.players;
    responseJson["questionCount"] = getRoomStateResponse.questionCount;
    responseJson["answerTimeout"] = getRoomStateResponse.answerTimeout;

    // Code
    buffer.push_back((unsigned char)RS_GETROOMSTATE);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes leaveRoom respone.
 *
 * @param leaveRoomResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(
    LeaveRoomResponse leaveRoomResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = leaveRoomResponse.status;

    // Code
    buffer.push_back((unsigned char)RS_LEAVEROOM);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes leaveGame respone.
 *
 * @param leaveGameResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(
    LeaveGameResponse leaveGameResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = leaveGameResponse.status;

    // Code
    buffer.push_back((unsigned char)RS_LEAVEGAME);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes getQuestion respone.
 *
 * @param getQuestionResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(
    GetQuestionResponse getQuestionResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = getQuestionResponse.status;
    responseJson["question"] = getQuestionResponse.question;
    responseJson["answers"] = getQuestionResponse.answers;

    // Code
    buffer.push_back((unsigned char)RS_GETQUESTION);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes submitAnswer respone.
 *
 * @param submitAnswerResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(
    SubmitAnswerResponse submitAnswerResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = submitAnswerResponse.status;
    responseJson["correctAnswer"] = submitAnswerResponse.correctAnswer;
    responseJson["score"] = submitAnswerResponse.score;

    // Code
    buffer.push_back((unsigned char)RS_SUBMITANSWER);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}

/**
 * @brief Serializes getGameResults respone.
 *
 * @param getGameResultsResponse Response to serialize.
 * @return std::vector<unsigned char> Serialized response.
 */
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(
    GetGameResultsResponse getGameResultsResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = getGameResultsResponse.status;
    responseJson["results"] = json::array();
    for (auto i : getGameResultsResponse.results) {
        json resultJson = json::object();
        resultJson["username"] = i.username;
        resultJson["correctAnswerCount"] = i.correctAnswerCount;
        resultJson["wrongAnswerCount"] = i.wrongAnswerCount;
        resultJson["averageAnswerTime"] = i.averageAnswerTime;
        resultJson["averageScore"] = i.averageScore;

        responseJson["results"].insert(responseJson["results"].end(),
                                       resultJson);
    }

    // Code
    buffer.push_back((unsigned char)RS_GETGAMERESULTS);

    // Length
    unsigned char len[4];
    long int intLen = sizeof(responseJson);

    memcpy(len, &intLen, sizeof(intLen));
    for (int i = 0; i < 4; i += sizeof(unsigned char))
        buffer.push_back(len[i]);

    // Message
    std::vector<unsigned char> msg = json::to_ubjson(responseJson);
    buffer.insert(buffer.end(), msg.begin(), msg.end());

    return buffer;
}
