#ifndef MENUREQUESTHANDLER_H_
#define MENUREQUESTHANDLER_H_

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler {
  public:
    MenuRequestHandler(LoggedUser user, RequestHandlerFactory *factory,
                       RoomManager *roomManager,
                       StatisticsManager *statisticsManager);

    bool isRequestRelevant(RequestInfo reqInf) override;
    RequestResult handleRequest(RequestInfo reqInf) override;

  private:
    LoggedUser m_user;
    RequestHandlerFactory &m_handlerFactory;
    RoomManager &m_roomManager;
    StatisticsManager &m_statisticsManager;

    RequestResult signout(RequestInfo reqInf);
    RequestResult getRooms(RequestInfo reqInf);
    RequestResult getPlayersInRoom(RequestInfo reqInf);
    RequestResult getPersonalStats(RequestInfo reqInf);
    RequestResult getHighScore(RequestInfo reqInf);
    RequestResult joinRoom(RequestInfo reqInf);
    RequestResult createRoom(RequestInfo reqInf);
};

#endif // !MENUREQUESTHANDLER_H_