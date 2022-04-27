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

    return newSignupRequest;
}