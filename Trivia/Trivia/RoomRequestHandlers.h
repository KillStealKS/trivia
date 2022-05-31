#ifndef ROOMREQUESTHANDLERS_H_
#define ROOMREQUESTHANDLERS_H_

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "RoomManager.h"

class RequestHandlerFactory;

class RoomRequestHandler : public IRequestHandler {
protected:
    Room m_room;
    LoggedUser m_user;
    RequestHandlerFactory& m_handlerFactory;
    RoomManager& m_roomManager;

    RoomRequestHandler(Room room, LoggedUser user,
        RequestHandlerFactory* factory, RoomManager* roomManager);
    
    RequestResult getRoomState(RequestInfo reqInf);
};



class RoomAdminRequestHandler : public RoomRequestHandler {
public:
    RoomAdminRequestHandler(Room room, LoggedUser user,
        RequestHandlerFactory* factory, RoomManager* roomManager);

    bool isRequestRelevant(RequestInfo reqInf);
    RequestResult handleRequest(RequestInfo reqInf);

private:
    RequestResult closeRoom(RequestInfo reqInf);
    RequestResult startGame(RequestInfo reqInf);
};



class RoomMemberRequestHandler : public RoomRequestHandler {
public:
    RoomMemberRequestHandler(Room room, LoggedUser user,
        RequestHandlerFactory* factory, RoomManager* roomManager);

    bool isRequestRelevant(RequestInfo reqInf);
    RequestResult handleRequest(RequestInfo reqInf);

private:
    RequestResult leaveRoom(RequestInfo reqInf);
};

#endif // !ROOMREQUESTHANDLERS_H_