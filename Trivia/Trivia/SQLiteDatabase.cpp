#include "SQLiteDatabase.h"
#include <string>

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
            "Email TEXT NOT NULL,"
            "Address TEXT NOT NULL,"
            "Phone TEXT NOT NULL,"
            "Date TEXT NOT NULL);";
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
                                std::string email, std::string addr,
                                std::string phone, std::string date) {
    char *errMsg;
    std::vector<User> userList;
    std::string sqlStatement =
        "INSERT INTO Users (Username, Password, Email, Address, Phone, Date)"
        " VALUES(\"" +
        username + "\", \"" + password + "\", \"" + email + "\", \"" + addr +
        "\", \"" + phone + "\", \"" + date + "\");";

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


//Question methods

/**
* @brief returns questions from the database
* 
* @param amount The amount of questions to return
*/
std::vector<Question> SQLiteDatabase::getQuestions(int amount) {
    char* errMsg;
    std::vector<Question> questionList;
    std::string sqlStatement = "SELECT * FROM Questions ORDER BY RANDOM() LIMIT " + 
        std::to_string(amount) + ";";

    int res = sqlite3_exec(m_Database, sqlStatement.c_str(),
        SQLiteDatabase::questionCallback, &questionList, &errMsg);
    if (res == SQLITE_OK)
        return questionList;
    else
        throw std::exception(__FUNCTION__ " - get questions failed");
}

/**
 * @brief callback function for Question
 */
int SQLiteDatabase::questionCallback(void* data, int argc, char** argv, char** azColName)
{
    std::vector<Question>* questionList = (std::vector<Question> *)data;
    Question question;

    for (int i = 0; i < argc; i++) {
        if (std::string(azColName[i]) == "ID")
            question.id = atoi(argv[i]);
        else if (std::string(azColName[i]) == "Question")
            question.question = argv[i];
        else if (std::string(azColName[i]) == "Answer")
            question.answer = argv[i];
        else if (std::string(azColName[i]) == "Incorrect1")
            question.incorrect1 = argv[i];
        else if (std::string(azColName[i]) == "Incorrect2")
            question.incorrect2 = argv[i];
        else if (std::string(azColName[i]) == "Incorrect3")
            question.incorrect3 = argv[i];
    }
    if (argc > 0)
        questionList->push_back(question);
    return 0;
}
