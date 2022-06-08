#include "GameRequestHandler.h"

/**
 * @brief Construct a new Game Request Handler:: Game Request Handler object
 *
 * @param user User.
 * @param factory Factory.
 * @param gameManager Game manager.
 * @param room Room.
 */
GameRequestHandler::GameRequestHandler(LoggedUser user,
                                       RequestHandlerFactory *factory,
                                       GameManager *gameManager, Room room)
    : m_user(user), m_handlerFactory(*factory), m_gameManager(*gameManager),
      m_game(m_gameManager.createGame(room)) {}

/**
 * @brief Checks if request is relevant.
 *
 * @param reqInf Request info.
 * @return true If request relevant.
 * @return false If request is not relevant.
 */
bool GameRequestHandler::isRequestRelevant(RequestInfo reqInf) {
    return (int)reqInf.buffer.front() == RQ_LEAVEGAME ||
           (int)reqInf.buffer.front() == RQ_GETQUESTION ||
           (int)reqInf.buffer.front() == RQ_SUBMITANSWER ||
           (int)reqInf.buffer.front() == RQ_GETGAMERESULTS;
}

/**
 * @brief Handle a request.
 *
 * @param reqInf Request info.
 * @return RequestResult Request result.
 */
RequestResult GameRequestHandler::handleRequest(RequestInfo reqInf) {
    RequestResult reqRes;

    try {
        switch ((int)reqInf.buffer.front()) {
        case RQ_LEAVEGAME:
            reqRes = leaveGame(reqInf);
            break;

        case RQ_GETQUESTION:
            reqRes = getQuestion(reqInf);
            break;

        case RQ_SUBMITANSWER:
            reqRes = submitAnswer(reqInf);
            break;

        case RQ_GETGAMERESULTS:
            reqRes = getGameResults(reqInf);
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
 * @brief LeaveGame request.
 *
 * @param reqInf Request info.
 * @return RequestResult Request result.
 */
RequestResult GameRequestHandler::leaveGame(RequestInfo reqInf) {
    m_game->removePlayer(m_user);

    LeaveGameResponse leaveGameRes = {1};
    return {JsonResponsePacketSerializer::serializeResponse(leaveGameRes),
            m_handlerFactory.createMenuRequestHandler(m_user)};
}

/**
 * @brief GetQuestion request.
 *
 * @param reqInf Request info.
 * @return RequestResult Request result.
 */
RequestResult GameRequestHandler::getQuestion(RequestInfo reqInf) {
    GetQuestionResponse getQuestionRes;
    if (m_game->arePlayersWaiting()) {
        Question currQuestion = m_game->getPlayers()[m_user].currentQuestion;

        unsigned int idCounter = 0;
        std::map<unsigned int, std::string> answers;
        for (auto i : currQuestion.getShuffledAnswers())
            answers[idCounter++] = i;

        getQuestionRes.answers = answers;
        getQuestionRes.question = currQuestion.getQuestion();
        getQuestionRes.status = 1;

        m_game->playerGotQuestion(m_user);
    } else {
        getQuestionRes.status = 0;
        m_game->insertWaiting(m_user);
    }

    return {JsonResponsePacketSerializer::serializeResponse(getQuestionRes),
            nullptr};
}

/**
 * @brief SubmitAnswer request.
 *
 * @param reqInf Request info.
 * @return RequestResult Request result.
 */
RequestResult GameRequestHandler::submitAnswer(RequestInfo reqInf) {
    Question currQuestion = m_game->getPlayers()[m_user].currentQuestion;
    m_game->submitAnswer(
        m_user, JsonResponsePacketDeserializer::deserializeSubmitAnswerRequest(
                    reqInf.buffer)
                    .answerId);

    unsigned int id = 0;
    SubmitAnswerResponse submitAnswerRes;
    for (auto i : currQuestion.getShuffledAnswers()) {
        if (i == currQuestion.getCorrectAnswer()) {
            submitAnswerRes.correctAnswer = id;
            break;
        }
        id++;
    }

    m_game->getQuestionForUser(m_user);

    if (m_game->didGameEndForUser(m_user))
        m_game->removePlayer(m_user);

    return {JsonResponsePacketSerializer::serializeResponse(submitAnswerRes),
            nullptr};
}

/**
 * @brief GetGameResults request.
 *
 * @param reqInf Request info.
 * @return RequestResult Request result.
 */
RequestResult GameRequestHandler::getGameResults(RequestInfo reqInf) {

    std::vector<PlayerResults> allPlayerResults;

    for (auto i : m_game->getPlayers()) {
        LoggedUser user = i.first;

        allPlayerResults.push_back(
            {user.getUsername(), i.second.correctAnswerCount,
             i.second.wrongAnswerCount, i.second.averageAnswerTime});
    }

    GetGameResultsResponse getGameResultsRes;

    if (m_game->didGameEnd()) {
        getGameResultsRes = {1, allPlayerResults};
        return {
            JsonResponsePacketSerializer::serializeResponse(getGameResultsRes),
            m_handlerFactory.createMenuRequestHandler(m_user)};
    } else {
        getGameResultsRes = {0, allPlayerResults};
        return {
            JsonResponsePacketSerializer::serializeResponse(getGameResultsRes),
            nullptr};
    }
}