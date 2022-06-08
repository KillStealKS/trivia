#include "Game.h"

/**
 * @brief Changes a user's question to the next one.
 *
 * @param user LoggedUser
 */
void Game::getQuestionForUser(LoggedUser user) {
    for (auto i = m_questions.begin(); i != m_questions.end(); i++) {
        if (i->getQuestion() == m_players[user].currentQuestion.getQuestion()) {
            if (++i != m_questions.end())
                m_players[user].currentQuestion = *(i);
            break;
        }
    }
}

/**
 * @brief Changes the user data according to his answer.
 *
 * @param user LoggedUser who answered.
 * @param answer The answer ID.
 */
void Game::submitAnswer(LoggedUser user, unsigned int answer, float timeToAnswer) {
    GameData &userData = m_players[user];

    userData.averageAnswerTime += timeToAnswer;

    if (m_players[user].currentQuestion.getShuffledAnswers()[answer] ==
        m_players[user].currentQuestion.getCorrectAnswer()) {
        userData.correctAnswerCount++;
        userData.scores.push_back((int)(1000 / (1 + timeToAnswer)));
    }
    else {
        userData.wrongAnswerCount++;
        userData.scores.push_back(0);
    }
}

/**
 * @brief Checks if all players are wating for question.
 *
 * @returns true if they are.
 * @returns false otherwise.
 */
bool Game::arePlayersWaiting() {
    return (m_playersWaiting.size() + m_playersGotQuestion.size()) ==
           m_players.size();
}

/**
 * @brief Inserts a player to waiting vector.
 *
 * @param user Player.
 */
void Game::insertWaiting(LoggedUser user) {
    for (auto i : m_playersWaiting) {
        if (user.getUsername() == i.getUsername())
            return;
    }
    m_playersWaiting.push_back(user);
}

/**
 * @brief Move player from wating vector to got question vector.
 *
 * @param user Player.
 */
void Game::playerGotQuestion(LoggedUser user) {
    for (auto i = m_playersWaiting.begin(); i != m_playersWaiting.end(); i++) {
        if (i->getUsername() == user.getUsername()) {
            m_playersWaiting.erase(i);
            break;
        }
    }
    m_playersGotQuestion.push_back(user);
    if (m_playersGotQuestion.size() == m_players.size())
        m_playersGotQuestion.clear();
}

/**
 * @brief Inserts a player to finished vector.
 *
 * @param user Player.
 */
void Game::removePlayer(LoggedUser user) {
    for (auto i : m_playersFinished) {
        if (i.getUsername() == user.getUsername())
            return;
    }

    m_playersFinished.push_back(user);
}

/**
 * @brief Remove a player from the finished vector. 
 * 
 * @param user Player
 */
void Game::removeFinished(LoggedUser user) {
    for (auto i = m_playersFinished.begin(); i != m_playersFinished.end(); i++) {
        if (i->getUsername() == user.getUsername()) {
            m_playersFinished.erase(i);
            break;
        }
    }
}

/**
 * @brief Checks if none of the players finished.
 *
 * @returns true if none of them did.
 * @returns false otherwise.
 */
bool Game::finishedEmpty() { return m_playersFinished.empty(); }

/**
 * @brief Checks if the user is on the last question.
 *
 * @param user LoggedUser.
 * @returns true if he is.
 * @returns false otherwise.
 */
bool Game::didGameEndForUser(LoggedUser user) {
    return m_players[user].currentQuestion.getQuestion() ==
           (m_questions.end() - 1)->getQuestion();
}

/**
 * @brief Checks if all players finished.
 *
 * @returns true if they did.
 * @returns false otherwise.
 */
bool Game::didGameEnd() { return m_playersFinished.size() == m_players.size(); }

void Game::insertOut(LoggedUser user) { m_playersOut.push_back(user); }

bool Game::allOut() { return m_players.size() == m_playersOut.size(); }
