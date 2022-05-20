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
        std::string sqlStatement = "CREATE TABLE Users ("
                                   "Username TEXT PRIMARY KEY NOT NULL,"
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
            throw std::exception(__FUNCTION__ " - creating Users table");
        }

        // creating Statistics
        sqlStatement = "CREATE TABLE Statistics ("
                       "Username TEXT PRIMARY KEY NOT NULL,"
                       "TotalGames INTEGER NOT NULL,"
                       "GamesWon INTEGER NOT NULL,"
                       "TotalAnswers INTEGER NOT NULL,"
                       "CorrectAnswers INTEGER NOT NULL,"
                       "TotalAnswerTime INTEGER NOT NULL,"
                       "Highscore INTEGER NOT NULL,"
                       "FOREIGN KEY(Username) REFERENCES Users(Username));";
        res = sqlite3_exec(m_Database, sqlStatement.c_str(), nullptr, nullptr,
                           &errMsg);
        if (res != SQLITE_OK) {
            std::cout << errMsg << std::endl;
            sqlite3_close(m_Database);
            m_Database = nullptr;
            throw std::exception(__FUNCTION__ " - creating Statistics table");
        }
    }

    return true;
}

// User methods

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

    // Users table insertion
    std::string sqlStatement =
        "INSERT INTO Users (Username, Password, Email, Address, Phone, Date)"
        " VALUES (\"" +
        username + "\", \"" + password + "\", \"" + email + "\", \"" + addr +
        "\", \"" + phone + "\", \"" + date + "\");";

    int res = sqlite3_exec(m_Database, sqlStatement.c_str(), nullptr, nullptr,
                           &errMsg);
    if (res != SQLITE_OK)
        throw std::exception(__FUNCTION__ " - database Users insertion failed");

    // Statistics table insertion
    sqlStatement =
        "INSERT INTO Statistics (Username, TotalGames, WonGames, TotalAnswers, "
        "CorrectAnswers, TotalAnswerTime, Highscore) "
        "VALUES (\"" +
        username + "\",0 ,0 ,0 ,0 ,0 ,0);";

    res = sqlite3_exec(m_Database, sqlStatement.c_str(), nullptr, nullptr,
                           &errMsg);
    if (res != SQLITE_OK)
        throw std::exception(
            __FUNCTION__ " - database Statistics insertion failed");
}

/**
 * @brief callback function for User
 */
int SQLiteDatabase::userCallback(void *data, int argc, char **argv,
                                 char **azColName) {
    std::vector<User> *userList = (std::vector<User> *)data;
    User user;

    for (int i = 0; i < argc; i++) {
        if (std::string(azColName[i]) == "Username")
            user.username = argv[i];
        else if (std::string(azColName[i]) == "Password")
            user.password = argv[i];
        else if (std::string(azColName[i]) == "Email")
            user.email = argv[i];
        else if (std::string(azColName[i]) == "Address")
            user.address = argv[i];
        else if (std::string(azColName[i]) == "Phone")
            user.phone = argv[i];
        else if (std::string(azColName[i]) == "Date")
            user.date = argv[i];
    }
    if (argc > 0)
        userList->push_back(user);
    return 0;
}

// Statistics methods

/**
 * @brief Gets a user's statistics.
 *
 * @param username User's username.
 * @return Statistics USer's statistics.
 */
Statistics SQLiteDatabase::getPlayerStatistics(std::string username) {
    char *errMsg;
    std::vector<Statistics> statisticsList;
    std::string sqlStatement =
        "SELECT * FROM Statistics WHERE Username = \"" + username + "\";";

    int res = sqlite3_exec(m_Database, sqlStatement.c_str(),
                           SQLiteDatabase::statisticsCallback, &statisticsList,
                           &errMsg);
    if (res == SQLITE_OK)
        return statisticsList[0];
    else
        throw std::exception(__FUNCTION__ " - player statistics failed");
}

/**
 * @brief Returns the average time it takes a player to answer questions
 *
 * @param username Name of the player
 */
float SQLiteDatabase::getPlayerAverageTime(std::string username) {
    char *errMsg;
    std::vector<Statistics> statisticsList;
    std::string sqlStatement =
        "SELECT * FROM Statistics WHERE Username = \"" + username + "\";";

    int res = sqlite3_exec(m_Database, sqlStatement.c_str(),
                           SQLiteDatabase::statisticsCallback, &statisticsList,
                           &errMsg);
    if (res == SQLITE_OK)
        return (float)statisticsList[0].totalAnswerTime /
               statisticsList[0].totalAnswers;
    else
        throw std::exception(__FUNCTION__ " - average answer time failed");
}

int SQLiteDatabase::getNumOfCorrectAnswers(std::string username) {
    char *errMsg;
    std::vector<Statistics> statisticsList;
    std::string sqlStatement =
        "SELECT * FROM Statistics WHERE Username = \"" + username + "\";";

    int res = sqlite3_exec(m_Database, sqlStatement.c_str(),
                           SQLiteDatabase::statisticsCallback, &statisticsList,
                           &errMsg);
    if (res == SQLITE_OK)
        return statisticsList[0].correctAnswers;
    else
        throw std::exception(
            __FUNCTION__ " - number of correct answers failed");
}

int SQLiteDatabase::getNumOfTotalAnswers(std::string username) {
    char *errMsg;
    std::vector<Statistics> statisticsList;
    std::string sqlStatement =
        "SELECT * FROM Statistics WHERE Username = \"" + username + "\";";

    int res = sqlite3_exec(m_Database, sqlStatement.c_str(),
                           SQLiteDatabase::statisticsCallback, &statisticsList,
                           &errMsg);
    if (res == SQLITE_OK)
        return statisticsList[0].totalAnswers;
    else
        throw std::exception(__FUNCTION__ " - total number of answers failed");
}

int SQLiteDatabase::getNumOfPlayerGames(std::string username) {
    char *errMsg;
    std::vector<Statistics> statisticsList;
    std::string sqlStatement =
        "SELECT * FROM Statistics WHERE Username = \"" + username + "\";";

    int res = sqlite3_exec(m_Database, sqlStatement.c_str(),
                           SQLiteDatabase::statisticsCallback, &statisticsList,
                           &errMsg);
    if (res == SQLITE_OK)
        return statisticsList[0].totalGames;
    else
        throw std::exception(__FUNCTION__ " - total number of games failed");
}

/**
 * @brief Gets highest scores.
 *
 * @param num Number of scores to get.
 * @return std::vector<std::string> Highest scores with usernames.
 */
std::vector<std::string> SQLiteDatabase::getHighscores(int amount) {
    char *errMsg;
    std::vector<Statistics> statisticsList;
    std::string sqlStatement =
        "SELECT * FROM Statistics ORDER BY Highscore LIMIT " +
        std::to_string(amount) + ";";

    int res = sqlite3_exec(m_Database, sqlStatement.c_str(),
                           SQLiteDatabase::statisticsCallback, &statisticsList,
                           &errMsg);
    if (res == SQLITE_OK) {
        std::vector<std::string> res;

        for (auto i : statisticsList) {
            res.push_back(std::to_string(i.highscore) + " - " + i.username);
        }

        return res;
    } else
        throw std::exception(__FUNCTION__ " - all time highscores failed");
}

/**
 * @brief Callback function for Statistics
 */
int SQLiteDatabase::statisticsCallback(void *data, int argc, char **argv,
                                       char **azColName) {
    std::vector<Statistics> *statisticsList = (std::vector<Statistics> *)data;
    Statistics statistics;

    for (int i = 0; i < argc; i++) {
        if (std::string(azColName[i]) == "Username")
            statistics.username = argv[i];
        else if (std::string(azColName[i]) == "TotalGames")
            statistics.totalGames = atoi(argv[i]);
        else if (std::string(azColName[i]) == "GamesWon")
            statistics.gamesWon = atoi(argv[i]);
        else if (std::string(azColName[i]) == "TotalAnswers")
            statistics.totalAnswers = atoi(argv[i]);
        else if (std::string(azColName[i]) == "CorrectAnswers")
            statistics.correctAnswers = atoi(argv[i]);
        else if (std::string(azColName[i]) == "TotalAnswerTime")
            statistics.totalAnswerTime = atoi(argv[i]);
        else if (std::string(azColName[i]) == "Highscore")
            statistics.highscore = atoi(argv[i]);
    }
    if (argc > 0)
        statisticsList->push_back(statistics);
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
