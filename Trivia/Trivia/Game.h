#ifndef GAME_H_
#define GAME_H_

#include "IDatabase.h"
#include "LoginManager.h"
#include <map>
#include <string>

struct GameData {
    Question currentQuestion;
    unsigned int correctAnswerCount;
    unsigned int wrongAnswerCount;
    float averageAnswerTime;
    std::vector<unsigned int> scores;
};

class Game {
  private:
    unsigned int m_id;
    std::vector<Question> m_questions;
    std::map<LoggedUser, GameData> m_players;
    std::vector<LoggedUser> m_playersWaiting;
    std::vector<LoggedUser> m_playersGotQuestion;
    std::vector<LoggedUser> m_playersFinished;
    std::vector<LoggedUser> m_playersOut;

  public:
    Game() {}
    Game(unsigned int id, std::vector<Question> questions,
         std::vector<std::string> players)
        : m_id(id), m_questions(questions) {
        for (auto i : players) {
            m_players.insert(std::pair<LoggedUser, GameData>(
                LoggedUser(i), GameData({m_questions[0], 0, 0, 0})));
            m_playersWaiting.push_back(LoggedUser(i));
        }
    }

    unsigned int getID() const { return m_id; }
    std::map<LoggedUser, GameData> getPlayers() { return m_players; }
    void getQuestionForUser(LoggedUser user);
    void submitAnswer(LoggedUser user, unsigned int answerID, float timeToAnswer);
    bool arePlayersWaiting();
    void insertWaiting(LoggedUser user);
    void playerGotQuestion(LoggedUser user);
    void removePlayer(LoggedUser user);
    void removeFinished(LoggedUser user);
    bool finishedEmpty();
    bool didGameEndForUser(LoggedUser user);
    bool didGameEnd();
    void insertOut(LoggedUser user);
    bool allOut();
};

#endif // !GAME_H_