#include "Serializer.h"

/**
 * @brief Serializes login request.
 *
 * @param loginRequest Request.
 * @return std::vector<unsigned char> Serialized request.
 */
std::vector<unsigned char>
Serializer::serializeRequest(LoginRequest loginRequest) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["username"] = loginRequest.username;
    responseJson["password"] = loginRequest.password;

    // Code
    buffer.push_back((unsigned char)RQ_LOGIN);

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
 * @brief Serializes signup request.
 *
 * @param signupRequest Request.
 * @return std::vector<unsigned char> Serialized request.
 */
std::vector<unsigned char>
Serializer::serializeRequest(SignupRequest signupRequest) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["username"] = signupRequest.username;
    responseJson["password"] = signupRequest.password;
    responseJson["email"] = signupRequest.email;
    responseJson["address"] = signupRequest.addr;
    responseJson["phone"] = signupRequest.phone;
    responseJson["date"] = signupRequest.date;

    // Code
    buffer.push_back((unsigned char)RQ_SIGNUP);

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
 * @brief Serializes getPlayersInRoom request.
 *
 * @param getPlayersRequest Request.
 * @return std::vector<unsigned char> Serialized request.
 */
std::vector<unsigned char>
Serializer::serializeRequest(GetPlayersInRoomRequest getPlayersRequest) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["roomId"] = getPlayersRequest.roomId;

    // Code
    buffer.push_back((unsigned char)RQ_GETPLAYERS);

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
 * @brief Serializes joinRoom request.
 *
 * @param joinRoomRequest Request.
 * @return std::vector<unsigned char> Serialized request.
 */
std::vector<unsigned char>
Serializer::serializeRequest(JoinRoomRequest joinRoomRequest) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["roomId"] = joinRoomRequest.roomId;

    // Code
    buffer.push_back((unsigned char)RQ_JOINROOM);

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
 * @brief Serializes createRoom request.
 *
 * @param createRoomRequest Request.
 * @return std::vector<unsigned char> Serialized request.
 */
std::vector<unsigned char>
Serializer::serializeRequest(CreateRoomRequest createRoomRequest) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["roomName"] = createRoomRequest.roomName;
    responseJson["maxUsers"] = createRoomRequest.maxUsers;
    responseJson["questionCount"] = createRoomRequest.questionCount;
    responseJson["answerTimeout"] = createRoomRequest.answerTimeout;

    // Code
    buffer.push_back((unsigned char)RQ_CREATEROOM);

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
 * @brief Serializes submitAnswer request.
 *
 * @param submitAnswerRequest Request.
 * @return std::vector<unsigned char> Serialized request.
 */
std::vector<unsigned char>
Serializer::serializeRequest(SubmitAnswerRequest submitAnswerRequest) {
    std::vector<unsigned char> buffer;
    json responseJson = json::object();
    responseJson["answerId"] = submitAnswerRequest.answerId;

    // Code
    buffer.push_back((unsigned char)RQ_SUBMITANSWER);

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
