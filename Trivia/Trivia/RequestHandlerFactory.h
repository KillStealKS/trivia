#ifndef REQUESTHANDLERFACTORY_H_
#define REQUESTHANDLERFACTORY_H_

#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomManager.h"
#include "RoomRequestHandlers.h"
#include "StatisticsManager.h"
#include "GameManager.h"
#include "GameRequestHandler.h"
#include <mutex>

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory {
  public:
    RequestHandlerFactory();

    IDatabase *getDatabase() const { return m_database; }
    LoginManager &getLoginManager() { return m_loginManager; }
    RoomManager &getRoomManager() { return m_roomManager; }
    StatisticsManager &getStatsManager() { return m_statisticsManager; }
    GameManager &getGameManager() { return m_gameManager; }

    LoginRequestHandler *createLoginRequestHandler();
    MenuRequestHandler *createMenuRequestHandler(LoggedUser user);
    RoomAdminRequestHandler *createRoomAdminRequestHandler(int roomID,
                                                           LoggedUser user);
    RoomMemberRequestHandler *createRoomMemberRequestHandler(int roomID,
                                                             LoggedUser user);
    GameRequestHandler *createGameRequestHandler(LoggedUser user, Room room);

  private:
    IDatabase *m_database;
    LoginManager m_loginManager;
    RoomManager m_roomManager;
    StatisticsManager m_statisticsManager;
    GameManager m_gameManager;
};

#endif // !REQUESTHANDLERFACTORY_H_