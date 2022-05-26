#include "RoomManager.h"

/**
 * @brief Creates a new room.
 *
 * @param user Room creator.
 * @param metadata Room metadata.
 */
void RoomManager::createRoom(LoggedUser user, RoomData metadata) {
    std::lock_guard<std::mutex> roomLock(*m_roomsMutex);
    m_rooms.insert({metadata.id, Room(user, metadata)});
}

/**
 * @brief Deletes a room.
 *
 * @param ID Room ID.
 */
void RoomManager::deleteRoom(int ID) {
    std::lock_guard<std::mutex> roomLock(*m_roomsMutex);
    m_rooms.erase(ID);
}

/**
 * @brief Get room state.
 *
 * @param ID Room ID.
 * @return unsigned int Room state.
 */
unsigned int RoomManager::getRoomState(int ID) {
    std::lock_guard<std::mutex> roomLock(*m_roomsMutex);
    return (m_rooms[ID].getMetadata().isActive); //?
}

/**
 * @brief Get rooms' metadata.
 *
 * @return std::vector<RoomData> Rooms' metadata.
 */
std::vector<RoomData> RoomManager::getRooms() {
    std::vector<RoomData> data;

    for (auto i : m_rooms) {
        data.push_back(i.second.getMetadata());
    }

    return data;
}

Room RoomManager::getRoom(int roomID) {
    for (auto i : m_rooms) {
        if (i.first == roomID)
            return i.second;
    }
    throw std::exception(__FUNCTION__ " - roomID not found.");
}
