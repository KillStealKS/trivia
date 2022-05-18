#include "LoginRequestHandler.h"

/*
 * @brief construct a new LoginRequestHandler::LoginRequestHandler object
 */
LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory *factory,
                                         LoginManager *manager)
    : m_handlerFactory(*factory), m_loginManager(*manager) {}

/*
 * @brief checks if the request code matches the request handler
 */
bool LoginRequestHandler::isRequestRelevant(RequestInfo ReqInf) {
    if (!((int)ReqInf.buffer.front() == RQ_LOGIN ||
          (int)ReqInf.buffer.front() == RQ_SIGNUP))
        return false;

    return true;
}

/*
 * @brief handles the user login request
 */
RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInf) {
    RequestResult reqRes;

    if (isRequestRelevant(reqInf)) {
        // login
        if (reqInf.buffer.front() == RQ_LOGIN) { // login
            LoginRequest userMsg =
                JsonResponsePacketDeserializer::deserializeLoginRequest(
                    reqInf.buffer);
            try {
                m_loginManager.login(userMsg.username, userMsg.password);
                LoginResponse loginRes = {RS_LOGIN};
                reqRes.response =
                    JsonResponsePacketSerializer::serializeResponse(loginRes);
                reqRes.newHandler = m_handlerFactory.createMenuRequestHandler();
            } catch (const std::exception &e) {
                ErrorResponse errRes = {e.what()};
                reqRes.response =
                    JsonResponsePacketSerializer::serializeResponse(errRes);
                reqRes.newHandler =
                    m_handlerFactory.createLoginRequestHandler();
            }
        } else if (reqInf.buffer.front() == RQ_SIGNUP) { // signup
            SignupRequest userMsg =
                JsonResponsePacketDeserializer::deserializeSignupRequest(
                    reqInf.buffer);
            try {
                m_loginManager.signup(userMsg.username, userMsg.password,
                                      userMsg.email, userMsg.addr,
                                      userMsg.phone, userMsg.date);
                SignupResponse signupRes = {RS_SIGNUP};
                reqRes.response =
                    JsonResponsePacketSerializer::serializeResponse(signupRes);
                reqRes.newHandler = m_handlerFactory.createMenuRequestHandler();
            } catch (const std::exception &e) {
                ErrorResponse errRes = {e.what()};
                reqRes.response =
                    JsonResponsePacketSerializer::serializeResponse(errRes);
                reqRes.newHandler =
                    m_handlerFactory.createLoginRequestHandler();
            }
        }
    } else { // error
        ErrorResponse errRes = {"Illegal message code."};
        reqRes.response =
            JsonResponsePacketSerializer::serializeResponse(errRes);
        reqRes.newHandler = m_handlerFactory.createLoginRequestHandler();
    }

    return reqRes;
}
