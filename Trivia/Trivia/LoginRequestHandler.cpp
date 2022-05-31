#include "LoginRequestHandler.h"

/*
 * @brief construct a new LoginRequestHandler::LoginRequestHandler object
 */
LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory *factory,
                                         LoginManager *loginManager)
    : m_handlerFactory(*factory), m_loginManager(*loginManager) {}

/*
 * @brief checks if the request code matches the request handler
 */
bool LoginRequestHandler::isRequestRelevant(RequestInfo ReqInf) {
    return (int)ReqInf.buffer.front() == RQ_LOGIN ||
           (int)ReqInf.buffer.front() == RQ_SIGNUP;
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
                LoggedUser user =
                    m_loginManager.login(userMsg.username, userMsg.password);
                LoginResponse loginRes = {RS_LOGIN};
                reqRes.response =
                    JsonResponsePacketSerializer::serializeResponse(loginRes);
                reqRes.newHandler =
                    m_handlerFactory.createMenuRequestHandler(user);
            } catch (const std::exception &e) {
                ErrorResponse errRes = {e.what()};
                reqRes.response =
                    JsonResponsePacketSerializer::serializeResponse(errRes);
                reqRes.newHandler = nullptr;
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
                reqRes.newHandler = nullptr;
            } catch (const std::exception &e) {
                ErrorResponse errRes = {e.what()};
                reqRes.response =
                    JsonResponsePacketSerializer::serializeResponse(errRes);
                reqRes.newHandler = nullptr;
            }
        }
    } else { // error
        ErrorResponse errRes = {"Illegal message code."};
        reqRes.response =
            JsonResponsePacketSerializer::serializeResponse(errRes);
        reqRes.newHandler = nullptr;
    }

    return reqRes;
}