#include "MenuRequestHandler.h"

/**
 * @brief Construct a new MenuRequestHandler::MenuRequestHandler object
 *
 * @param user User.
 * @param factory Request handler factory.
 * @param roomManager Room manager.
 * @param statisticsManager Statistics manager.
 */
MenuRequestHandler::MenuRequestHandler(LoggedUser user,
                                       RequestHandlerFactory *factory,
                                       RoomManager *roomManager,
                                       StatisticsManager *statisticsManager)
    : m_user(user), m_handlerFactory(*factory), m_roomManager(*roomManager),
      m_statisticsManager(*statisticsManager) {}

/**
 * @brief Checks if request is relevant.
 *
 * @param RI Request info.
 * @return true If request relevant.
 * @return false If request is not relevant.
 */
bool MenuRequestHandler::isRequestRelevant(RequestInfo RI) {
    return (int)RI.buffer.front() == RQ_LOGOUT ||
           (int)RI.buffer.front() == RQ_GETPLAYERS ||
           (int)RI.buffer.front() == RQ_GETROOM ||
           (int)RI.buffer.front() == RQ_JOINROOM ||
           (int)RI.buffer.front() == RQ_CREATEROOM ||
           (int)RI.buffer.front() == RQ_HIGHSCORE;
}

/**
 * @brief Handle a request.
 *
 * @param reqInf Request info.
 * @return RequestResult Request result.
 */
RequestResult MenuRequestHandler::handleRequest(RequestInfo reqInf) {
    RequestResult reqRes;

    try {
        switch ((int)reqInf.buffer.front()) {
        case RQ_LOGOUT:
            reqRes = signout(reqInf);
            break;

        case RQ_GETPLAYERS:
            reqRes = getPlayersInRoom(reqInf);
            break;

        case RQ_GETROOM:
            reqRes = getRooms(reqInf);
            break;

        case RQ_JOINROOM:
            reqRes = joinRoom(reqInf);
            break;

        case RQ_CREATEROOM:
            reqRes = createRoom(reqInf);
            break;

        case RQ_PERSONALSTATS:
            reqRes = getPersonalStats(reqInf);
            break;

        case RQ_HIGHSCORE:
            reqRes = getHighScore(reqInf);
            break;

        default:
            ErrorResponse errRes = {"Illegal message code."};
            reqRes.response =
                JsonResponsePacketSerializer::serializeResponse(errRes);
            reqRes.newHandler = nullptr;
            break;
        }
    } catch (const std::exception &e) {
        ErrorResponse errRes = {e.what()};
        reqRes.response =
            JsonResponsePacketSerializer::serializeResponse(errRes);
        reqRes.newHandler = nullptr;
    }

    return reqRes;
}

/**
 * @brief Singout request.
 *
 * @param reqInf Request info.
 * @return RequestResult Request result.
 */
RequestResult MenuRequestHandler::signout(RequestInfo reqInf) {
    LoginManager &loginManager = m_handlerFactory.getLoginManager();
    loginManager.logout(m_user.getUsername());

    LogoutResponse logoutRes = {1};

    RequestResult reqRes = {
        JsonResponsePacketSerializer::serializeResponse(logoutRes),
        m_handlerFactory.createLoginRequestHandler()};
    return reqRes;
}

/**
 * @brief GetRooms request.
 *
 * @param reqInf Request info.
 * @return RequestResult Request result.
 */
RequestResult MenuRequestHandler::getRooms(RequestInfo reqInf) {
    GetRoomsResponse getRoomsRes = {1, m_roomManager.getRooms()};

    RequestResult reqRes = {
        JsonResponsePacketSerializer::serializeResponse(getRoomsRes), nullptr};
    return reqRes;
}

/**
 * @brief GetPlayersInRoom request.
 *
 * @param reqInf Request info.
 * @return RequestResult Request result.
 */
RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo reqInf) {
    GetPlayersInRoomRequest getPlayersReq =
        JsonResponsePacketDeserializer::deserializeGetPlayersRequest(
            reqInf.buffer);

    GetPlayersInRoomResponse getPlayersRes = {
        m_roomManager.getRoom(getPlayersReq.roomId).getAllUsers()};

    RequestResult reqRes = {
        JsonResponsePacketSerializer::serializeResponse(getPlayersRes),
        nullptr};
    return reqRes;
}

/**
 * @brief GetPersonalStats request.
 *
 * @param reqInf Request info.
 * @return RequestResult Request result.
 */
RequestResult MenuRequestHandler::getPersonalStats(RequestInfo reqInf) {
    GetPersonalStatsResponse getPersonalStatsRes = {
        1, m_statisticsManager.getUserStatistics(m_user.getUsername())};

    RequestResult reqRes = {
        JsonResponsePacketSerializer::serializeResponse(getPersonalStatsRes),
        nullptr};
    return reqRes;
}

/**
 * @brief GetHighscore request.
 *
 * @param reqInf Request info.
 * @return RequestResult Request result.
 */
RequestResult MenuRequestHandler::getHighScore(RequestInfo reqInf) {
    std::vector<std::string> highscores = m_statisticsManager.getHighScore(3);
    GetHighScoreResponse highscoreRes = {1, highscores};

    RequestResult reqRes = {
        JsonResponsePacketSerializer::serializeResponse(highscoreRes), nullptr};
    return reqRes;
}

/**
 * @brief JoinRoom request.
 *
 * @param reqInf Request info.
 * @return RequestResult Request result.
 */
RequestResult MenuRequestHandler::joinRoom(RequestInfo reqInf) {
    JoinRoomRequest joinRoomReq =
        JsonResponsePacketDeserializer::deserializeJoinRoomRequest(
            reqInf.buffer);

    Room room = m_roomManager.getRoom(joinRoomReq.roomId);

    if (room.getMetadata().maxPlayers == room.getAllUsers().size())
        throw std::exception("Room is full.");

    room.addUser(m_user);

    JoinRoomResponse joinRoomRes = {1};

    RequestResult reqRes = {
        JsonResponsePacketSerializer::serializeResponse(joinRoomRes), 
        m_handlerFactory.createRoomMemberRequestHandler(room, m_user)};
    return reqRes;
}

/**
 * @brief CreateRoom request.
 *
 * @param reqInf Request info.
 * @return RequestResult Request result.
 */
RequestResult MenuRequestHandler::createRoom(RequestInfo reqInf) {
    CreateRoomRequest createRoomReq =
        JsonResponsePacketDeserializer::deserializeCreateRoomRequest(
            reqInf.buffer);

    RoomData roomData = {m_roomManager.getRooms().size() + 1,
                         createRoomReq.roomName, createRoomReq.maxUsers,
                         createRoomReq.questionCount, 0};
    m_roomManager.createRoom(m_user, roomData);

    CreateRoomResponse createRoomRes = {1};

    RequestResult reqRes = {
        JsonResponsePacketSerializer::serializeResponse(createRoomRes),
        m_handlerFactory.createRoomAdminRequestHandler(
            m_roomManager.getRoom(roomData.id), m_user)};
    return reqRes;
}