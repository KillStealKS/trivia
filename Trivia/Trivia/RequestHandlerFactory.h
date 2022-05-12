#ifndef REQUESTHANDLERFACTORY_H_
#define REQUESTHANDLERFACTORY_H_

#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "MenuRequestHandler.h"
#include <mutex>

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory {
public:
	RequestHandlerFactory();

	IDatabase* getDatabase() const { return m_database; }

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();

private:
	IDatabase* m_database;
	LoginManager m_loginManager;
};

#endif // !REQUESTHANDLERFACTORY_H_