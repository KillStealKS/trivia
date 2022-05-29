#ifndef STATISTICSMANAGER_H_
#define STATISTICSMANAGER_H_

#include "IDatabase.h"

class StatisticsManager {
  private:
    IDatabase *m_database;

  public:
    StatisticsManager(IDatabase *database);

    std::vector<std::string> getHighScore(int amount);
    Statistics getUserStatistics(std::string username);

    std::mutex *m_databaseMutex;
};

#endif // !STATISTICSMANAGER_H_
