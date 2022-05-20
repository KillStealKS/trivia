#pragma once
#include <io.h>
#include <iostream>
#include <mutex>
#include <string>
#include <vector>

typedef struct User {
    std::string username;
    std::string password;
    std::string email;
    std::string address;
    std::string phone;
    std::string date;
} User;

typedef struct Statistics {
    std::string username;
    int totalGames;
    int gamesWon;
    int totalAnswers;
    int correctAnswers;
    int totalAnswerTime;
    int highscore;
} Statistics;

typedef struct Question {
    int id;
    std::string question;
    std::string answer;
    std::string incorrect1;
    std::string incorrect2;
    std::string incorrect3;
} Question;

class IDatabase {
  public:
    virtual ~IDatabase() = default;

    virtual bool open() = 0;

    // User methods
    virtual bool doesUserExist(std::string username) = 0;
    virtual bool doesPasswordMatch(std::string username,
                                   std::string password) = 0;
    virtual void addNewUser(std::string username, std::string password,
                            std::string email, std::string addr,
                            std::string phone, std::string date) = 0;

    // Statistics methods
    virtual Statistics getPlayerStatistics(std::string username) = 0;
    virtual float getPlayerAverageTime(std::string username) = 0;
    virtual int getNumOfCorrectAnswers(std::string username) = 0;
    virtual int getNumOfTotalAnswers(std::string username) = 0;
    virtual int getNumOfPlayerGames(std::string username) = 0;
    virtual std::vector<std::string> getHighscores(int num) = 0;
    
    //Question methods
    virtual std::vector<Question> getQuestions(int amount) = 0;
};