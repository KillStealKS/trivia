#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <map>
#include <mutex>
#include <vector>

#include "Game.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class GameManager {
private:
    IDatabase *m_database;
    std::vector<Game*> m_games;

public:
    GameManager(IDatabase* database) : m_database(database) {}

    Game* createGame(Room room);
    void deleteGame(unsigned int id);
};

#endif // !GAMEMANAGER_H_