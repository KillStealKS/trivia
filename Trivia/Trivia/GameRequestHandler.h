#ifndef GAMEREQUESTHANDLER_H_
#define GAMEREQUESTHANDLER_H_

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler {
public:
    GameRequestHandler(LoggedUser user, RequestHandlerFactory* factory,
        GameManager* gameManager, Room room);

    bool isRequestRelevant(RequestInfo reqInf) override;
    RequestResult handleRequest(RequestInfo reqInf) override;

private:
    LoggedUser m_user;
    RequestHandlerFactory& m_handlerFactory;
    GameManager& m_gameManager;
    Game* m_game;

    RequestResult leaveGame(RequestInfo reqInf);
    RequestResult getQuestion(RequestInfo reqInf);
    RequestResult submitAnswer(RequestInfo reqInf);
    RequestResult getGameResults(RequestInfo reqInf);
};

#endif // !GAMEREQUESTHANDLER_H_