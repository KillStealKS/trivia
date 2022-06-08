#pragma once
#include <io.h>
#include <iostream>
#include <mutex>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

struct User {
    std::string username;
    std::string password;
    std::string email;
    std::string address;
    std::string phone;
    std::string date;
};

struct Statistics {
    std::string username;
    int totalGames;
    int gamesWon;
    int totalAnswers;
    int correctAnswers;
    float totalAnswerTime;
    int highscore;
};

class Question
{
public:
    std::string getQuestion() const { return m_question; }
    std::string getCorrectAnswer() const { return m_correctAnswer; }
    std::vector<std::string> getShuffledAnswers() const { return m_shuffledAnswers; }

    void setID(const int id) { m_id = id; }
    void setQuestion(const std::string question) { m_question = question; }
    void setCorrectAnswer(const std::string correctAnswer) { m_correctAnswer = correctAnswer; }
    void insertIncorrctAnswer(const std::string incorrectAnswer) 
        { m_incorrectAnswers.push_back(incorrectAnswer); }
    void setShuffledAnswers(std::vector<std::string> shuffledAnswers) {
        std::random_shuffle(shuffledAnswers.begin(), shuffledAnswers.end());
        m_shuffledAnswers = shuffledAnswers;
    }

private:
    int m_id;
    std::string m_question;
    std::string m_correctAnswer;
    std::vector<std::string> m_incorrectAnswers;
    std::vector<std::string> m_shuffledAnswers;
};

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

    virtual int updateUserStatistics(std::string username, Statistics newStats) = 0;

    // Question methods
    virtual std::vector<Question> getQuestions(int amount) = 0;
};