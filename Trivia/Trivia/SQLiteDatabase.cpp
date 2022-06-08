#include "SQLiteDatabase.h"
#include <string>

/**
 * @brief opens the database, creating it if needed
 */
bool SQLiteDatabase::open() {
    const char *gameDBFileName = "MyTriviaDB.sqlite",
               *questionDBFileName = "../../questions.sqlite";
    char *errMsg = nullptr;

    // opening database, creating if needed
    int res = sqlite3_open(questionDBFileName, &m_questionDatabase);
    if (res != SQLITE_OK) {
        m_questionDatabase = nullptr;
        throw std::exception("Question database open failed.");
    }

    // checking if game database exists
    const int doesFileExist = _access(gameDBFileName, 0);

    // opening database, creating if needed
    res = sqlite3_open(gameDBFileName, &m_gameDatabase);
    if (res != SQLITE_OK) {
        m_gameDatabase = nullptr;
        throw std::exception("Game database open failed.");
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
        res = sqlite3_exec(m_gameDatabase, sqlStatement.c_str(), nullptr,
                           nullptr, &errMsg);
        if (res != SQLITE_OK) {
            std::cout << errMsg << std::endl;
            sqlite3_close(m_gameDatabase);
            m_gameDatabase = nullptr;
            throw std::exception("Creating Users table failed.");
        }

        // creating Statistics
        sqlStatement = "CREATE TABLE Statistics ("
                       "Username TEXT PRIMARY KEY NOT NULL,"
                       "TotalGames INTEGER NOT NULL,"
                       "GamesWon INTEGER NOT NULL,"
                       "TotalAnswers INTEGER NOT NULL,"
                       "CorrectAnswers INTEGER NOT NULL,"
                       "TotalAnswerTime FLOAT NOT NULL,"
                       "Highscore INTEGER NOT NULL,"
                       "FOREIGN KEY(Username) REFERENCES Users(Username));";
        res = sqlite3_exec(m_gameDatabase, sqlStatement.c_str(), nullptr,
                           nullptr, &errMsg);
        if (res != SQLITE_OK) {
            std::cout << errMsg << std::endl;
            sqlite3_close(m_gameDatabase);
            m_gameDatabase = nullptr;
            throw std::exception("Creating Statistics table failed.");
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

    int res = sqlite3_exec(m_gameDatabase, sqlStatement.c_str(),
                           SQLiteDatabase::userCallback, &userList, &errMsg);
    if (res == SQLITE_OK)
        return !userList.empty();
    else
        throw std::exception("User exists check failed.");
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

    int res = sqlite3_exec(m_gameDatabase, sqlStatement.c_str(),
                           SQLiteDatabase::userCallback, &userList, &errMsg);
    if (res == SQLITE_OK)
        return !userList.empty();
    else
        throw std::exception("Password match check failed.");
}

/**
 * @brief adds a user to the database
 */
void SQLiteDatabase::addNewUser(std::string username, std::string password,
                                std::string email, std::string addr,
                                std::string phone, std::string date) {
    char *errMsg;

    // Users table insertion
    std::string sqlStatement =
        "INSERT INTO Users (Username, Password, Email, Address, Phone, Date)"
        " VALUES (\"" +
        username + "\", \"" + password + "\", \"" + email + "\", \"" + addr +
        "\", \"" + phone + "\", \"" + date + "\");";

    int res = sqlite3_exec(m_gameDatabase, sqlStatement.c_str(), nullptr,
                           nullptr, &errMsg);
    if (res != SQLITE_OK) {
        std::cout << errMsg;
        throw std::exception("Database Users insertion failed.");
    }

    // Statistics table insertion
    sqlStatement =
        "INSERT INTO Statistics (Username, TotalGames, GamesWon, TotalAnswers, "
        "CorrectAnswers, TotalAnswerTime, Highscore) "
        "VALUES (\"" +
        username + "\", 0, 0, 0, 0, 0, 0);";

    res = sqlite3_exec(m_gameDatabase, sqlStatement.c_str(), nullptr, nullptr,
                       &errMsg);
    if (res != SQLITE_OK) {
        std::cout << errMsg;
        throw std::exception("Database Statistics insertion failed.");
    }
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

    int res = sqlite3_exec(m_gameDatabase, sqlStatement.c_str(),
                           SQLiteDatabase::statisticsCallback, &statisticsList,
                           &errMsg);
    if (res == SQLITE_OK)
        return statisticsList[0];
    else
        throw std::exception("Get player statistics failed.");
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

    int res = sqlite3_exec(m_gameDatabase, sqlStatement.c_str(),
                           SQLiteDatabase::statisticsCallback, &statisticsList,
                           &errMsg);
    if (res == SQLITE_OK)
        return statisticsList[0].totalAnswerTime /
               statisticsList[0].totalAnswers;
    else
        throw std::exception("Get average answer time failed.");
}

/**
 * @brief Returns the amount of answers a player has guessed correctly
 *
 * @param username Name of the player
 */
int SQLiteDatabase::getNumOfCorrectAnswers(std::string username) {
    char *errMsg;
    std::vector<Statistics> statisticsList;
    std::string sqlStatement =
        "SELECT * FROM Statistics WHERE Username = \"" + username + "\";";

    int res = sqlite3_exec(m_gameDatabase, sqlStatement.c_str(),
                           SQLiteDatabase::statisticsCallback, &statisticsList,
                           &errMsg);
    if (res == SQLITE_OK)
        return statisticsList[0].correctAnswers;
    else
        throw std::exception("Get number of correct answers failed.");
}

/**
 * @brief Returns the amount of answers a player has answered
 *
 * @param username Name of the player
 */
int SQLiteDatabase::getNumOfTotalAnswers(std::string username) {
    char *errMsg;
    std::vector<Statistics> statisticsList;
    std::string sqlStatement =
        "SELECT * FROM Statistics WHERE Username = \"" + username + "\";";

    int res = sqlite3_exec(m_gameDatabase, sqlStatement.c_str(),
                           SQLiteDatabase::statisticsCallback, &statisticsList,
                           &errMsg);
    if (res == SQLITE_OK)
        return statisticsList[0].totalAnswers;
    else
        throw std::exception("Get total number of answers failed.");
}

/**
 * @brief Returns the amount of games a player has played
 *
 * @param username Name of the player
 */
int SQLiteDatabase::getNumOfPlayerGames(std::string username) {
    char *errMsg;
    std::vector<Statistics> statisticsList;
    std::string sqlStatement =
        "SELECT * FROM Statistics WHERE Username = \"" + username + "\";";

    int res = sqlite3_exec(m_gameDatabase, sqlStatement.c_str(),
                           SQLiteDatabase::statisticsCallback, &statisticsList,
                           &errMsg);
    if (res == SQLITE_OK)
        return statisticsList[0].totalGames;
    else
        throw std::exception("Get total number of games failed.");
}

/**
 * @brief Gets highest scores.
 *
 * @param amount Number of scores to get.
 * @return std::vector<std::string> Highest scores with usernames.
 */
std::vector<std::string> SQLiteDatabase::getHighscores(int amount) {
    char *errMsg;
    std::vector<Statistics> statisticsList;
    std::string sqlStatement =
        "SELECT * FROM Statistics ORDER BY Highscore LIMIT " +
        std::to_string(amount) + ";";

    int res = sqlite3_exec(m_gameDatabase, sqlStatement.c_str(),
                           SQLiteDatabase::statisticsCallback, &statisticsList,
                           &errMsg);
    if (res == SQLITE_OK) {
        std::vector<std::string> highscores;

        for (auto i : statisticsList) {
            highscores.push_back(std::to_string(i.highscore) + " - " +
                                 i.username);
        }

        return highscores;
    } else
        throw std::exception("Get all time highscores failed.");
}

/**
 * @brief Updates a user's Statistics table.
 *
 * @param username Name of the user.
 * @param newStats Statistics from the latest game needed to be added to the old
 * ones.
 * @return 0 if successful.
 */
int SQLiteDatabase::updateUserStatistics(std::string username,
                                         Statistics newStats) {
    Statistics oldStats = getPlayerStatistics(username);

    newStats.totalGames += oldStats.totalGames;
    newStats.gamesWon += oldStats.gamesWon;
    newStats.totalAnswers += oldStats.totalAnswers;
    newStats.correctAnswers += oldStats.correctAnswers;
    newStats.totalAnswerTime += oldStats.totalAnswerTime;
    if (oldStats.highscore > newStats.highscore)
        newStats.highscore = oldStats.highscore;

    // Statistics table update
    char *errMsg;
    std::string sqlStatement =
        "UPDATE Statistics SET TotalGames = " +
        std::to_string(newStats.totalGames) +
        ", GamesWon = " + std::to_string(newStats.gamesWon) +
        ", TotalAnswers = " + std::to_string(newStats.totalAnswers) +
        ", CorrectAnswers = " + std::to_string(newStats.correctAnswers) +
        ", TotalAnswerTime = " + std::to_string(newStats.totalAnswerTime) +
        ", Highscore = " + std::to_string(newStats.highscore) +
        " WHERE Username = \"" + username + "\";";

    int res = sqlite3_exec(m_gameDatabase, sqlStatement.c_str(), nullptr,
                           nullptr, &errMsg);
    if (res != SQLITE_OK) {
        std::cout << errMsg;
        throw std::exception("User Statistics update failed.");
    }
    return 0;
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
            statistics.totalAnswerTime = std::stof(argv[i]);
        else if (std::string(azColName[i]) == "Highscore")
            statistics.highscore = atoi(argv[i]);
    }
    if (argc > 0)
        statisticsList->push_back(statistics);
    return 0;
}

// Question methods

/**
 * @brief returns questions from the database
 *
 * @param amount The amount of questions to return
 */
std::vector<Question> SQLiteDatabase::getQuestions(int amount) {
    char *errMsg;
    std::vector<Question> questionList;
    std::string sqlStatement =
        "SELECT * FROM Questions ORDER BY RANDOM() LIMIT " +
        std::to_string(amount) + ";";

    int res =
        sqlite3_exec(m_questionDatabase, sqlStatement.c_str(),
                     SQLiteDatabase::questionCallback, &questionList, &errMsg);
    if (res == SQLITE_OK)
        return questionList;
    else {
        std::cout << errMsg << std::endl;
        throw std::exception("Get questions failed");
    }
}

/**
 * @brief callback function for Question
 */
int SQLiteDatabase::questionCallback(void *data, int argc, char **argv,
                                     char **azColName) {
    std::vector<Question> *questionList = (std::vector<Question> *)data;
    Question question;
    std::vector<std::string> allAnswers;

    for (int i = 0; i < argc; i++) {
        if (std::string(azColName[i]) == "ID")
            question.setID(atoi(argv[i]));
        else if (std::string(azColName[i]) == "Question")
            question.setQuestion(argv[i]);
        else if (std::string(azColName[i]) == "Answer") {
            question.setCorrectAnswer(argv[i]);
            allAnswers.push_back(argv[i]);
        } else if (std::string(azColName[i]) == "Incorrect1") {
            question.insertIncorrctAnswer(argv[i]);
            allAnswers.push_back(argv[i]);
        } else if (std::string(azColName[i]) == "Incorrect2") {
            question.insertIncorrctAnswer(argv[i]);
            allAnswers.push_back(argv[i]);
        } else if (std::string(azColName[i]) == "Incorrect3") {
            question.insertIncorrctAnswer(argv[i]);
            allAnswers.push_back(argv[i]);
        }
    }
    if (argc > 0)
        question.setShuffledAnswers(allAnswers);
    questionList->push_back(question);
    return 0;
}
