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

    bool operator<(const LoggedUser other) const { return m_username < other.m_username; }
  private:
    std::string m_username;
};

class LoginManager {
  public:
    LoginManager(IDatabase *database);

    void signup(std::string username, std::string password, std::string email,
                std::string addr, std::string phone, std::string date);
    LoggedUser login(std::string username, std::string password);
    void logout(std::string username);

  private:
    std::vector<LoggedUser> m_loggedUsers;
    IDatabase *m_database;
    std::mutex *m_usersMutex, *m_databaseMutex;
};