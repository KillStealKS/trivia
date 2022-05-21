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
std::vector<unsigned char> serializeResponse(LogoutResponse logoutResponse) {
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
std::vector<unsigned char> serializeResponse(GetRoomsResponse getRoomResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["status"] = getRoomResponse.status;
    for (auto r : getRoomResponse.rooms) {
        json roomJson = json::object();
        roomJson["name"] = r.name;
        roomJson["maxPlayers"] = r.maxPlayers;
        roomJson["numOfQuestions"] = r.numOfQuestions;
        roomJson["timePerQuestion"] = r.timePerQuestion;
        roomJson["isActive"] = r.isActive;

        responseJson["rooms"][r.id] = roomJson;
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
std::vector<unsigned char>
serializeResponse(GetPlayersInRoomResponse getPlayersResponse) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["playersInRoom"] = getPlayersResponse.players;

    // Code
    buffer.push_back((unsigned char)RS_PLAYERSINROOM);

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
std::vector<unsigned char>
serializeResponse(JoinRoomResponse joinRoomResponse) {
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
std::vector<unsigned char>
serializeResponse(CreateRoomResponse createRoomResponse) {
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
std::vector<unsigned char>
serializeResponse(GetPersonalStatsResponse getStatsResponse) {
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