#include "LoginManager.h"

// ************* LoggedUser methods *************

/*
 * @brief LoggedUser constructor
 */
LoggedUser::LoggedUser(std::string username) : m_username(username) {}

/*
 * @brief username getter
 */
const std::string LoggedUser::getUsername() { return m_username; }

/*
 * @brief username setter
 */
void LoggedUser::setUsername(const std::string username) {
    m_username = username;
}

// ************* LoginManager methods *************

/*
 * @brief construct a new LoginManager::LoginManager object
 */
LoginManager::LoginManager(IDatabase *database)
    : m_database(database), m_databaseMutex(new std::mutex),
      m_usersMutex(new std::mutex) {}

/*
 * @brief adds a user to the database
 */
void LoginManager::signup(std::string username, std::string password,
                          std::string email, std::string addr,
                          std::string phone, std::string date) {
    if (!m_database->doesUserExist(
            username)) // don't want 2 users with the same username
        std::lock_guard<std::mutex> databaseLock(*m_databaseMutex);
    m_database->addNewUser(username, password, email, addr, phone, date);
}

/*
 * @brief logs in a user
 */
LoggedUser LoginManager::login(std::string username, std::string password) {
    if (!m_database->doesUserExist(username))
        throw std::exception("Username not found.");

    for (auto i : m_loggedUsers) {
        if (i.getUsername() == username)
            throw std::exception("User already logged in.");
    }

    if (m_database->doesPasswordMatch(username, password)) {
        LoggedUser user(username);
        std::lock_guard<std::mutex> usersLock(*m_usersMutex);
        m_loggedUsers.push_back(user);
        return user;
    } else
        throw std::exception("Wrong password.");
}

/*
 * @brief logs out a user
 */
void LoginManager::logout(std::string username) {
    for (auto i = m_loggedUsers.begin(); i != m_loggedUsers.end(); i++) {
        if (i->getUsername() == username) {
            m_loggedUsers.erase(i);
            break;
        }
    }
}