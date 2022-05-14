#pragma once
#include <io.h>
#include <iostream>
#include <mutex>
#include <vector>

typedef struct User {
    int id;
    std::string username;
    std::string password;
    std::string email;
} User;

class IDatabase {
  public:
    virtual ~IDatabase() = default;

    virtual bool open() = 0;

    virtual bool doesUserExist(std::string username) = 0;
    virtual bool doesPasswordMatch(std::string username,
                                   std::string password) = 0;
    virtual void addNewUser(std::string username, std::string password,
                            std::string email) = 0;
};