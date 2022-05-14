#pragma once

#include "SQLiteDatabase.h"
#include <iostream>
#include <mutex>
#include <vector>


class LoggedUser {
  public:
    LoggedUser(std::string username);

    const std::string getUsername();
    void setUsername(const std::string username);

  private:
    std::string m_username;
};

class LoginManager {
  public:
    LoginManager(IDatabase *database);

    void signup(std::string username, std::string password, std::string email);
    void login(std::string username, std::string password);
    void logout(std::string username);

  private:
    std::vector<LoggedUser> m_loggedUsers;
    IDatabase *m_database;
    std::mutex *m_usersMutex, *m_databaseMutex;
};