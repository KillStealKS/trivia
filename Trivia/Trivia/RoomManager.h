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

  public:
    RoomManager() : m_roomsMutex(new std::mutex) {}

    void createRoom(LoggedUser user, RoomData metadata);
    void deleteRoom(int ID);
    unsigned int getRoomState(int ID);
    std::vector<RoomData> getRooms();

    Room getRoom(int roomID);
};

#endif // !ROOMMANAGER_H_