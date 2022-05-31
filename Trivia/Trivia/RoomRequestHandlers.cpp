#include "RoomRequestHandlers.h"

/**
 * @brief Construct a new RoomRequestHandler::RoomRequestHandler object
 *
 * @param room Room
 * @param user User.
 * @param factory Request handler factory.
 * @param roomManager Room manager.
 * @param statisticsManager Statistics manager.
 */
RoomRequestHandler::RoomRequestHandler(Room room, LoggedUser user, 
    RequestHandlerFactory* factory, RoomManager* roomManager) 
    : m_room(room), m_user(user), 
    m_handlerFactory(*factory), m_roomManager(*roomManager) {}

/**
 * @brief Returns the state of the room.
 * 
 * @param reqInf RequestInfo.
 * @returns RequestResult.
 */
RequestResult RoomRequestHandler::getRoomState(RequestInfo reqInf) {
    RoomData roomData = m_room.getMetadata();
    
    GetRoomStateResponse roomStateRes = { 1,
        (bool)roomData.isActive, m_room.getAllUsers(),
        roomData.numOfQuestions, roomData.timePerQuestion };

    RequestResult reqRes = {JsonResponsePacketSerializer::serializeResponse(roomStateRes), nullptr };
    return reqRes;
}



/**
 * @brief Construct a new RoomAdminRequestHandler::RoomAdminRequestHandler object
 *
 * @param room Room
 * @param user User.
 * @param factory Request handler factory.
 * @param roomManager Room manager.
 * @param statisticsManager Statistics manager.
 */
RoomAdminRequestHandler::RoomAdminRequestHandler(Room room, LoggedUser user,
    RequestHandlerFactory* factory, RoomManager* roomManager)
    : RoomRequestHandler(room, user, factory, roomManager) {}

/**
 * @brief Checks if request is relevant.
 *
 * @param reqInf Request info.
 * @return true If request relevant.
 * @return false If request is not relevant.
 */
bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo reqInf) {
    return (int)reqInf.buffer.front() == RQ_CLOSEROOM ||
           (int)reqInf.buffer.front() == RQ_STARTGAME ||
           (int)reqInf.buffer.front() == RQ_GETROOMSTATE;
}

/**
 * @brief Handle a request.
 *
 * @param reqInf Request info.
 * @return RequestResult Request result.
 */
RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo reqInf) {
    RequestResult reqRes;

    try {
        switch ((int)reqInf.buffer.front())
        {
        case RQ_CLOSEROOM:
            reqRes = closeRoom(reqInf);
            break;

        case RQ_STARTGAME:
            reqRes = startGame(reqInf);
            break;

        case RQ_GETROOMSTATE:
            reqRes = getRoomState(reqInf);
            break;

        default:
            ErrorResponse errRes = { "Illegal message code." };
            reqRes.response =
                JsonResponsePacketSerializer::serializeResponse(errRes);
            reqRes.newHandler = nullptr;
            break;
        };
    } catch (const std::exception& e) {
        ErrorResponse errRes = { e.what() };
        reqRes.response =
            JsonResponsePacketSerializer::serializeResponse(errRes);
        reqRes.newHandler = nullptr;
    }

    return reqRes;
}

/**
 * @brief Closes the room, removing all users in it.
 *
 * @return RequestResult
 */
RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo reqInf) {
    for (auto i : m_room.getAllUsers()) {
        m_room.removeUser(LoggedUser(i));
    }

    m_roomManager.deleteRoom(m_room.getMetadata().id);
    

    CloseRoomResponse closeRoomRes = { 1 };
    return { JsonResponsePacketSerializer::serializeResponse(closeRoomRes),
    m_handlerFactory.createMenuRequestHandler(m_user) };
}

/**
 * @brief Starts the game in the room.
 *
 * @return RequestResult
 */
RequestResult RoomAdminRequestHandler::startGame(RequestInfo reqInf) {
    m_room.setIsActive(1);

    StartGameResponse startGameRes = { 1 };
    return { JsonResponsePacketSerializer::serializeResponse(startGameRes),
        nullptr };
}



/**
 * @brief Construct a new RoomMemberRequestHandler::RoomMemberRequestHandler object
 *
 * @param room Room
 * @param user User.
 * @param factory Request handler factory.
 * @param roomManager Room manager.
 * @param statisticsManager Statistics manager.
 */
RoomMemberRequestHandler::RoomMemberRequestHandler(Room room, LoggedUser user, 
    RequestHandlerFactory* factory, RoomManager* roomManager)
    : RoomRequestHandler(room, user, factory, roomManager) {}

/**
 * @brief Checks if request is relevant.
 *
 * @param reqInf Request info.
 * @return true If request relevant.
 * @return false If request is not relevant.
 */
bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo reqInf) {
    return (int)reqInf.buffer.front() == RQ_LEAVEROOM ||
        (int)reqInf.buffer.front() == RQ_GETROOMSTATE;
}

/**
 * @brief Handle a request.
 *
 * @param reqInf Request info.
 * @return RequestResult Request result.
 */
RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo reqInf) {
    RequestResult reqRes;

    try {
        switch ((int)reqInf.buffer.front())
        {
        case RQ_LEAVEROOM:
            reqRes = leaveRoom(reqInf);
            break;

        case RQ_GETROOMSTATE:
            reqRes = getRoomState(reqInf);
            break;

        default:
            ErrorResponse errRes = { "Illegal message code." };
            reqRes.response =
                JsonResponsePacketSerializer::serializeResponse(errRes);
            reqRes.newHandler = nullptr;
            break;
        };
    }
    catch (const std::exception& e) {
        ErrorResponse errRes = { e.what() };
        reqRes.response =
            JsonResponsePacketSerializer::serializeResponse(errRes);
        reqRes.newHandler = nullptr;
    }

    return reqRes;
}

/**
 * @brief Disconnects the user from the room he's in.
 * 
 * @param reqInf RequestInfo.
 * @returns RequestResult.
 */
RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo reqInf) {
    m_room.removeUser(m_user.getUsername());
    
    LeaveRoomResponse leaveRoomRes = { 1 };
    return { JsonResponsePacketSerializer::serializeResponse(leaveRoomRes),
        m_handlerFactory.createMenuRequestHandler(m_user) };
}