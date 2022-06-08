#include "RequestHandlerFactory.h"

/*
 * @brief construct a new RequestHandlerFactory::RequestHandlerFactory object
 */
RequestHandlerFactory::RequestHandlerFactory()
    : m_database(new SQLiteDatabase()), m_loginManager(m_database),
      m_statisticsManager(m_database), m_gameManager(m_database) {
    m_database->open();
}

/*
 * @brief creates a new LoginRequestHandler
 */
LoginRequestHandler *RequestHandlerFactory::createLoginRequestHandler() {
    return new LoginRequestHandler(this, &m_loginManager);
}

/*
 * @brief creates a new MenuRequestHandler
 */
MenuRequestHandler *
RequestHandlerFactory::createMenuRequestHandler(LoggedUser user) {
    return new MenuRequestHandler(user, this, &m_roomManager,
                                  &m_statisticsManager);
}

/*
 * @brief creates a new RoomAdminRequestHandler
 */
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(int roomID, LoggedUser user) {
    return new RoomAdminRequestHandler(roomID, user, this, &m_roomManager);
}

/*
 * @brief creates a new RoomMemberRequestHandler
 */
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(int roomID, LoggedUser user) {
    return new RoomMemberRequestHandler(roomID, user, this, &m_roomManager);
}

/*
 * @brief creates a new GameRequestHandler
 */
GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser user, Room room)
{
    return new GameRequestHandler(user, this, &m_gameManager, room);
}