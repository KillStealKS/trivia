#ifndef REQUESTHANDLERFACTORY_H_
#define REQUESTHANDLERFACTORY_H_

#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include <mutex>

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory {
  public:
    RequestHandlerFactory();

    IDatabase *getDatabase() const { return m_database; }
    LoginManager &getLoginManager() { return m_loginManager; }
    RoomManager &getRoomManager() { return m_roomManager; }
    StatisticsManager &getStatsManager() { return m_statisticsManager; }

    LoginRequestHandler *createLoginRequestHandler();
    MenuRequestHandler *createMenuRequestHandler(LoggedUser user);

  private:
    IDatabase *m_database;
    LoginManager m_loginManager;
    RoomManager m_roomManager;
    StatisticsManager m_statisticsManager;
};

#endif // !REQUESTHANDLERFACTORY_H_