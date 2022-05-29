#include "RequestHandler.h"

/**
 * @brief Handles login request.
 *
 * @param username
 * @param password
 * @return LoginResponse Response.
 */
LoginResponse RequestHandler::loginRequest(std::string username,
                                           std::string password) {
    LoginRequest request = {username, password};

    std::vector<unsigned char> serializedRequest =
        Serializer::serializeRequest(request);
    std::vector<unsigned char> serializedResponse =
        Communicator::communicator.sendRequest(serializedRequest);

    if (serializedResponse[0] == RS_ERROR) {
        ErrorResponse response =
            Deserializer::deserializeErrorResponse(serializedResponse);
        throw std::exception(response.message.c_str());
    } else {
        LoginResponse response =
            Deserializer::deserializeLoginResponse(serializedResponse);
        return response;
    }
}

/**
 * @brief Handles signup request.
 *
 * @param username
 * @param password
 * @param email
 * @param addr
 * @param phone
 * @param date
 * @return SignupResponse Response.
 */
SignupResponse
RequestHandler::signupRequest(std::string username, std::string password,
                              std::string email, std::string addr,
                              std::string phone, std::string date) {
    if (!std::regex_match(username, std::regex(".*")))
        throw std::exception("Invalid username");
    if (!std::regex_match(password,
                          std::regex("^(?=.*[A-Za-z])(?=.*\\d)(?=.*[@$!%*#?&])["
                                     "A-Za-z\\d@$!%*#?&]{3,}$")))
        throw std::exception("Invalid password");
    if (!std::regex_match(email, std::regex("^\\S+@\\S+$")))
        throw std::exception("Invalid email");
    if (!std::regex_match(addr, std::regex("^\([A-z]+, \\d+, [A-z]+\)$")))
        throw std::exception("Invalid address");
    if (!std::regex_match(phone, std::regex("^0\\d{1,2}\\d{7}$")))
        throw std::exception("Invalid phone");
    if (!std::regex_match(
            date,
            std::regex("^((\\d{2}\\/\\d{2}\\/\\d{4})|(\\d{2}\\.\\d{2}\\.\\d{4}))$")))
        throw std::exception("Invalid date");

    SignupRequest request = {username, password, email, addr, phone, date};

    std::vector<unsigned char> serializedRequest =
        Serializer::serializeRequest(request);
    std::vector<unsigned char> serializedResponse =
        Communicator::communicator.sendRequest(serializedRequest);

    if (serializedResponse[0] == RS_ERROR) {
        ErrorResponse response =
            Deserializer::deserializeErrorResponse(serializedResponse);
        throw std::exception(response.message.c_str());
    } else {
        SignupResponse response =
            Deserializer::deserializeSignupResponse(serializedResponse);
        return response;
    }
}

/**
 * @brief Handles logout request.
 *
 * @return LogoutResponse Response.
 */
LogoutResponse RequestHandler::logoutRequest() {
    std::vector<unsigned char> serializedRequest{(unsigned char)RQ_LOGOUT};
    std::vector<unsigned char> serializedResponse =
        Communicator::communicator.sendRequest(serializedRequest);

    if (serializedResponse[0] == RS_ERROR) {
        ErrorResponse response =
            Deserializer::deserializeErrorResponse(serializedResponse);
        throw std::exception(response.message.c_str());
    } else {
        LogoutResponse response =
            Deserializer::deserializeLogoutResponse(serializedResponse);
        return response;
    }
}

/**
 * @brief Handles getPlayersInRoom request.
 *
 * @param roomId
 * @return GetPlayersInRoomResponse Response.
 */
GetPlayersInRoomResponse
RequestHandler::getPlayersInRoomRequest(unsigned int roomId) {
    GetPlayersInRoomRequest request = {roomId};

    std::vector<unsigned char> serializedRequest =
        Serializer::serializeRequest(request);
    std::vector<unsigned char> serializedResponse =
        Communicator::communicator.sendRequest(serializedRequest);

    if (serializedResponse[0] == RS_ERROR) {
        ErrorResponse response =
            Deserializer::deserializeErrorResponse(serializedResponse);
        throw std::exception(response.message.c_str());
    } else {
        GetPlayersInRoomResponse response =
            Deserializer::deserializeGetPlayersInRoomResponse(
                serializedResponse);
        return response;
    }
}

/**
 * @brief Handles getRooms request.
 *
 * @return GetRoomsResponse Response.
 */
GetRoomsResponse RequestHandler::getRoomsRequest() {
    std::vector<unsigned char> serializedRequest{(unsigned char)RQ_GETROOMS};
    std::vector<unsigned char> serializedResponse =
        Communicator::communicator.sendRequest(serializedRequest);

    if (serializedResponse[0] == RS_ERROR) {
        ErrorResponse response =
            Deserializer::deserializeErrorResponse(serializedResponse);
        throw std::exception(response.message.c_str());
    } else {
        GetRoomsResponse response =
            Deserializer::deserializeGetRoomsResponse(serializedResponse);
        return response;
    }
}

/**
 * @brief Handles joinRoom request.
 *
 * @param roomId
 * @return JoinRoomResponse Response.
 */
JoinRoomResponse RequestHandler::joinRoomRequest(unsigned int roomId) {
    JoinRoomRequest request = {roomId};

    std::vector<unsigned char> serializedRequest =
        Serializer::serializeRequest(request);
    std::vector<unsigned char> serializedResponse =
        Communicator::communicator.sendRequest(serializedRequest);

    if (serializedResponse[0] == RS_ERROR) {
        ErrorResponse response =
            Deserializer::deserializeErrorResponse(serializedResponse);
        throw std::exception(response.message.c_str());
    } else {
        JoinRoomResponse response =
            Deserializer::deserializeJoinRoomResponse(serializedResponse);
        return response;
    }
}

/**
 * @brief Handles createRoom request.
 *
 * @param roomName
 * @param maxUsers
 * @param questionCount
 * @param answerTimeout
 * @return CreateRoomResponse Response.
 */
CreateRoomResponse
RequestHandler::createRoomRequest(std::string roomName, unsigned int maxUsers,
                                  unsigned int questionCount,
                                  unsigned int answerTimeout) {
    CreateRoomRequest request = {roomName, maxUsers, questionCount,
                                 answerTimeout};

    std::vector<unsigned char> serializedRequest =
        Serializer::serializeRequest(request);
    std::vector<unsigned char> serializedResponse =
        Communicator::communicator.sendRequest(serializedRequest);

    if (serializedResponse[0] == RS_ERROR) {
        ErrorResponse response =
            Deserializer::deserializeErrorResponse(serializedResponse);
        throw std::exception(response.message.c_str());
    } else {
        CreateRoomResponse response =
            Deserializer::deserializeCreateRoomResponse(serializedResponse);
        return response;
    }
}

/**
 * @brief Handle getHighScore request.
 *
 * @return GetHighScoreResponse Response.
 */
GetHighScoreResponse RequestHandler::getHighscoreRequest() {
    std::vector<unsigned char> serializedRequest{(unsigned char)RQ_HIGHSCORE};
    std::vector<unsigned char> serializedResponse =
        Communicator::communicator.sendRequest(serializedRequest);

    if (serializedResponse[0] == RS_ERROR) {
        ErrorResponse response =
            Deserializer::deserializeErrorResponse(serializedResponse);
        throw std::exception(response.message.c_str());
    } else {
        GetHighScoreResponse response =
            Deserializer::deserializeGetHishscoreResponse(serializedResponse);
        return response;
    }
}

/**
 * @brief Handles getPersonalStats request.
 *
 * @return GetPersonalStatsResponse Response.
 */
GetPersonalStatsResponse RequestHandler::getPersonalStatsRequest() {
    std::vector<unsigned char> serializedRequest{
        (unsigned char)RQ_PERSONALSTATS};
    std::vector<unsigned char> serializedResponse =
        Communicator::communicator.sendRequest(serializedRequest);

    if (serializedResponse[0] == RS_ERROR) {
        ErrorResponse response =
            Deserializer::deserializeErrorResponse(serializedResponse);
        throw std::exception(response.message.c_str());
    } else {
        GetPersonalStatsResponse response =
            Deserializer::deserializePersonalStatsResponse(serializedResponse);
        return response;
    }
}