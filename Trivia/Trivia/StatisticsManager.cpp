#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase *database)
    : m_database(database), m_databaseMutex(new std::mutex) {}

/**
 * @brief Gets top 5 scores.
 *
 * @return std::vector<std::string> String vector containing scores.
 */
std::vector<std::string> StatisticsManager::getHighScore(int amount) {
    return m_database->getHighscores(amount);
}

/**
 * @brief Gets user statistics.
 *
 * @param username User's username.
 * @return Statistics User's statistics.
 */
Statistics StatisticsManager::getUserStatistics(std::string username) {
    return m_database->getPlayerStatistics(username);
}