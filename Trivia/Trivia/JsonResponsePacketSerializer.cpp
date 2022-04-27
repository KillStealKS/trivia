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
 * @param errorResponse Response to serialize.
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
 * @param errorResponse Response to serialize.
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
