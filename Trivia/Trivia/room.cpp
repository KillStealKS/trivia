#include "Room.h"

/**
 * @brief Construct a new Room::Room object.
 *
 * @param user Room creator.
 * @param metadata Room metadata.
 */
Room::Room(LoggedUser user, RoomData metadata) : m_metadata(metadata) {
    m_users.push_back(user);
}

/**
 * @brief Adds a user to the room.
 *
 * @param user User to add.
 */
void Room::addUser(LoggedUser user) {
    for (auto i : m_users) {
        if (i.getUsername() == user.getUsername())
            throw std::exception("User already connected.");
    }
    m_users.push_back(user);
}

/**
 * @brief Removes a user from the room.
 *
 * @param user User to remove.
 */
void Room::removeUser(LoggedUser user) {
    for (auto i = m_users.begin(); i != m_users.end(); i++) {
        if (i->getUsername() == user.getUsername()) {
            m_users.erase(i);
            return;
        }
    }
}

/**
 * @brief Gets all users currently in the room.
 *
 * @return std::vector<std::string> A vector containing all connected users'
 * names.
 */
std::vector<std::string> Room::getAllUsers() {
    std::vector<std::string> users;

    for (auto u : m_users)
        users.push_back(u.getUsername());

    return users;
}

/**
 * @brief Sets isActive in the room metadata.
 *
 * @param newVal const unsigned int.
 */
void Room::setIsActive(const unsigned int newVal) { m_metadata.isActive = newVal; }
