#ifndef ROOM_H_
#define ROOM_H_

#include "LoginManager.h"
#include <string>

typedef struct RoomData {
    unsigned int id;
    std::string name;
    unsigned int maxPlayers;
    unsigned int numOfQuestions;
    unsigned int timePerQuestion;
    unsigned int isActive;
} RoomData;

class Room {
  private:
    RoomData m_metadata;
    std::vector<LoggedUser> m_users;

  public:
    Room() {}
    Room(LoggedUser user, RoomData metadata);

    void addUser(LoggedUser user);
    void removeUser(LoggedUser user);
    std::vector<std::string> getAllUsers();

    RoomData getMetadata() { return m_metadata; }
};

#endif // !ROOM_H_