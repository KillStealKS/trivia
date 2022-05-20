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

typedef struct Question {
    int id;
    std::string question;
    std::string answer;
    std::string incorrect1;
    std::string incorrect2;
    std::string incorrect3;
};

class IDatabase {
  public:
    virtual ~IDatabase() = default;

    virtual bool open() = 0;

    virtual bool doesUserExist(std::string username) = 0;
    virtual bool doesPasswordMatch(std::string username,
                                   std::string password) = 0;
    virtual void addNewUser(std::string username, std::string password,
                            std::string email, std::string addr,
                            std::string phone, std::string date) = 0;

    //Question methods
    virtual std::vector<Question> getQuestions(int amount) = 0;
};