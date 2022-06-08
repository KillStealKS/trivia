#ifndef ROOMMANAGER_H_
#define ROOMMANAGER_H_

#include "LoginManager.h"
#include "Room.h"
#include <map>
#include <mutex>
#include <vector>

class RoomManager {
  private:
    std::map<int, Room> m_rooms;
    std::mutex *m_roomsMutex;
    int m_currentID = 1;

  public:
    RoomManager() : m_roomsMutex(new std::mutex) {}

    void createRoom(LoggedUser user, RoomData metadata);
    void deleteRoom(int ID);
    unsigned int getRoomState(int ID);
    std::vector<RoomData> getRooms();

    Room* getRoom(int roomID);
    int getCurrentID() { return m_currentID; }
};

#endif // !ROOMMANAGER_H_