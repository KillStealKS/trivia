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
			for (auto j : players) {	//TODO
				if (overallHighscore < j.second.correctAnswerCount) {
					winnerUser = j.first;
					overallHighscore = j.second.correctAnswerCount;
				}
			}

			//updating database
			for (auto j : players) {
				tempUser = j.first;	//needed because keys in a map are always constants

				tempStats.totalGames = 1;
				if (tempUser.getUsername() == winnerUser.getUsername())
					tempStats.gamesWon = 1;
				else
					tempStats.gamesWon = 0;
				tempStats.totalAnswers = j.second.correctAnswerCount + j.second.wrongAnswerCount;
				tempStats.correctAnswers = j.second.correctAnswerCount;
				tempStats.totalAnswerTime = 0;	//TODO
				tempStats.highscore = j.second.correctAnswerCount;	//TODO

				m_database->updateUserStatistics(tempUser.getUsername(), tempStats);
			}

			delete *i;
			m_games.erase(i);
			break;
		}
	}
}