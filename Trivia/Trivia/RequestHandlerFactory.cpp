#include "RequestHandlerFactory.h"

/*
 * @brief construct a new RequestHandlerFactory::RequestHandlerFactory object
 */
RequestHandlerFactory::RequestHandlerFactory()
    : m_database(new SQLiteDatabase()), m_loginManager(m_database) {
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
MenuRequestHandler *RequestHandlerFactory::createMenuRequestHandler() {
    return new MenuRequestHandler;
}
