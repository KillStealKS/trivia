#ifndef STATISTICSMANAGER_H_
#define STATISTICSMANAGER_H_

#include "IDatabase.h"

class StatisticsManager {
  private:
    IDatabase *m_database;

  public:
    std::vector<std::string> getHighScore(int amount);
    Statistics getUserStatistics(std::string username);
};

#endif // !STATISTICSMANAGER_H_
