#include "SQLiteDatabase.h"

/**
 * @brief opens the database, creating it if needed
 */
bool SQLiteDatabase::open() {
    const char *DBFileName = "MyTriviaDB.sqlite";
    char *errMsg = nullptr;

    // checking if database exists
    const int doesFileExist = _access(DBFileName, 0);

    // opening database, creating if needed
    int res = sqlite3_open(DBFileName, &m_Database);
    if (res != SQLITE_OK) {
        m_Database = nullptr;
        throw std::exception(__FUNCTION__ " - database open");
    }

    // creating schema if file was created
    if (doesFileExist != 0) {
        // creating Users table
        std::string sqlStatement =
            "CREATE TABLE Users ("
            "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            "Username TEXT NOT NULL,"
            "Password TEXT NOT NULL,"
            "Email TEXT NOT NULL);";
        res = sqlite3_exec(m_Database, sqlStatement.c_str(), nullptr, nullptr,
                           &errMsg);
        if (res != SQLITE_OK) {
            std::cout << errMsg << std::endl;
            sqlite3_close(m_Database);
            m_Database = nullptr;
            throw std::exception(__FUNCTION__ " - creating table");
        }
    }

    return true;
}

/**
 * @brief checks in the database if a username exists
 */
bool SQLiteDatabase::doesUserExist(std::string username) {
    char *errMsg;
    std::vector<User> userList;
    std::string sqlStatement =
        "SELECT * FROM Users WHERE Username = \"" + username + "\"; ";

    int res = sqlite3_exec(m_Database, sqlStatement.c_str(),
                           SQLiteDatabase::userCallback, &userList, &errMsg);
    if (res == SQLITE_OK)
        return !userList.empty();
    else
        throw std::exception(__FUNCTION__ " - user exists check failed");
}

/**
 * @brief checks in the database if the password matches the username
 */
bool SQLiteDatabase::doesPasswordMatch(std::string username,
                                       std::string password) {
    char *errMsg;
    std::vector<User> userList;
    std::string sqlStatement = "SELECT * FROM Users WHERE Username = \"" +
                               username + "\" AND Password = \"" + password +
                               "\";";

    int res = sqlite3_exec(m_Database, sqlStatement.c_str(),
                           SQLiteDatabase::userCallback, &userList, &errMsg);
    if (res == SQLITE_OK)
        return !userList.empty();
    else
        throw std::exception(__FUNCTION__ " - password match check failed");
}

/**
 * @brief adds a user to the database
 */
void SQLiteDatabase::addNewUser(std::string username, std::string password,
                                std::string email) {
    char *errMsg;
    std::vector<User> userList;
    std::string sqlStatement = "INSERT INTO Users (Username, Password, Email)"
                               " VALUES(\"" +
                               username + "\", \"" + password + "\", \"" +
                               email + "\"); ";

    int res = sqlite3_exec(m_Database, sqlStatement.c_str(), nullptr, nullptr,
                           &errMsg);
    if (res != SQLITE_OK)
        throw std::exception(__FUNCTION__ " - database insertion failed");
}

/**
 * @brief callback function for User
 */
int SQLiteDatabase::userCallback(void *data, int argc, char **argv,
                                 char **azColName) {
    std::vector<User> *userList = (std::vector<User> *)data;
    User user;

    for (int i = 0; i < argc; i++) {
        if (std::string(azColName[i]) == "ID")
            user.id = atoi(argv[i]);
        else if (std::string(azColName[i]) == "Username")
            user.username = argv[i];
        else if (std::string(azColName[i]) == "Password")
            user.password = argv[i];
        else if (std::string(azColName[i]) == "Email")
            user.email = argv[i];
    }
    if (argc > 0)
        userList->push_back(user);
    return 0;
}