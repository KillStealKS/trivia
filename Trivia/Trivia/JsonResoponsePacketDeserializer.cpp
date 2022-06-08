#include "JsonResponsePacketDeserializer.h"

/**
 * @brief Deserializes login request.
 *
 * @param buffer Serialized request.
 * @return LoginRequest Deserialized request.
 */
LoginRequest JsonResponsePacketDeserializer::deserializeLoginRequest(
    std::vector<unsigned char> buffer) {
    LoginRequest newLoginRequest;

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

    newLoginRequest.username = msg["username"];
    newLoginRequest.password = msg["password"];

    return newLoginRequest;
}

/**
 * @brief Deserializes signup request.
 *
 * @param buffer Serialized request.
 * @return SignupRequest Deserialized request.
 */
SignupRequest JsonResponsePacketDeserializer::deserializeSignupRequest(
    std::vector<unsigned char> buffer) {
    SignupRequest newSignupRequest;

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

    newSignupRequest.username = msg["username"];
    newSignupRequest.password = msg["password"];
    newSignupRequest.email = msg["email"];
    newSignupRequest.addr = msg["address"];
    newSignupRequest.phone = msg["phone"];
    newSignupRequest.date = msg["date"];

    return newSignupRequest;
}

/**
 * @brief Deserializes getPlayersInRoom request.
 *
 * @param buffer Serialized request.
 * @return GetPlayersInRoomRequest Deserialized request.
 */
GetPlayersInRoomRequest
JsonResponsePacketDeserializer::deserializeGetPlayersRequest(
    std::vector<unsigned char> buffer) {
    GetPlayersInRoomRequest newGetPlayersRequest;

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

    newGetPlayersRequest.roomId = msg["roomId"];

    return newGetPlayersRequest;
}

/**
 * @brief Deserializes joinRoom request.
 *
 * @param buffer Serialized request.
 * @return JoinRoomRequest Deserialized request.
 */
JoinRoomRequest JsonResponsePacketDeserializer::deserializeJoinRoomRequest(
    std::vector<unsigned char> buffer) {
    JoinRoomRequest newJoinRoomRequest;

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

    newJoinRoomRequest.roomId = msg["roomId"];

    return newJoinRoomRequest;
}

/**
 * @brief Deserializes createRoom request.
 *
 * @param buffer Serialized request.
 * @return CreateRoomRequest Deserialized request.
 */
CreateRoomRequest JsonResponsePacketDeserializer::deserializeCreateRoomRequest(
    std::vector<unsigned char> buffer) {
    CreateRoomRequest newCreateRoomRequest;

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

    newCreateRoomRequest.roomName = msg["roomName"];
    newCreateRoomRequest.maxUsers = msg["maxUsers"];
    newCreateRoomRequest.questionCount = msg["questionCount"];
    newCreateRoomRequest.answerTimeout = msg["answerTimeout"];

    return newCreateRoomRequest;
}

/**
 * @brief Deserializes submitAnswer request.
 *
 * @param buffer Serialized request.
 * @return SubmitAnswerRequest Deserialized request.
 */
SubmitAnswerRequest
JsonResponsePacketDeserializer::deserializeSubmitAnswerRequest(
    std::vector<unsigned char> buffer) {
    SubmitAnswerRequest newSubmitAnswerRequest;

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

    newSubmitAnswerRequest.answerId = msg["answerId"];
    newSubmitAnswerRequest.timeRemaining = msg["timeRemaining"];

    return newSubmitAnswerRequest;
}
