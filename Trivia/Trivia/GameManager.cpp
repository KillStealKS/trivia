#include "GameManager.h"

/**
 * @brief Creates a Game object given a room.
 * 
 * @param room Room object.
 * @returns Game.
 */
Game* GameManager::createGame(Room room) {
	for (auto i : m_games) {
		if (i->getID() == room.getMetadata().id)
			return i;
	}
	Game* newGame = new Game(room.getMetadata().id, m_database->getQuestions(room.getMetadata().numOfQuestions),
		room.getAllUsers());
	
	m_games.insert(m_games.end(), newGame);
	return newGame;
}

/**
 * @brief Logs the game results in the database and deletes the game.
 * 
 * @param id Game ID.
 */
void GameManager::deleteGame(unsigned int id) {
	Statistics tempStats;
	LoggedUser tempUser(""), winnerUser("");
	unsigned int overallHighscore = 0;

	for (auto i = m_games.begin(); i != m_games.end(); i++) {
		if ((*i)->getID() == id) {
			auto players = (*i)->getPlayers();

			//determining winner
			for (auto j : players) {
				unsigned int playerHighscore = 0;
				for (auto k : j.second.scores)
					playerHighscore += k;
				playerHighscore /= j.second.correctAnswerCount + j.second.wrongAnswerCount;

				if (overallHighscore < playerHighscore) {
					winnerUser = j.first;
					overallHighscore = playerHighscore;
				}
			}

			//updating database
			for (auto j : players) {
				tempUser = j.first;	//needed because keys in a map are always constants

				tempStats.totalGames = 1;
				tempStats.gamesWon = (tempUser.getUsername() == 
					winnerUser.getUsername() ? 1 : 0);
				tempStats.totalAnswers = j.second.correctAnswerCount + j.second.wrongAnswerCount;
				tempStats.correctAnswers = j.second.correctAnswerCount;
				tempStats.totalAnswerTime = j.second.averageAnswerTime;

				unsigned int playerHighscore = 0;
				for (auto k : j.second.scores)
					playerHighscore += k;
				playerHighscore /= j.second.correctAnswerCount + j.second.wrongAnswerCount;
				tempStats.highscore = playerHighscore;

				m_database->updateUserStatistics(tempUser.getUsername(), tempStats);
			}

			delete *i;
			m_games.erase(i);
			break;
		}
	}
}