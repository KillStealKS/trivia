#ifndef SQLITEDATABASE_H_
#define SQLITEDATABASE_H_

#include "IDatabase.h"
#include "sqlite3.h"

class SQLiteDatabase : public IDatabase {
  public:
    SQLiteDatabase() = default;
    ~SQLiteDatabase() = default;

    bool open() override;

    bool doesUserExist(std::string username) override;
    bool doesPasswordMatch(std::string username, std::string password) override;
    void addNewUser(std::string username, std::string password,
                    std::string email) override;
    static int userCallback(void *data, int argc, char **argv,
                            char **azColName);

  private:
    sqlite3 *m_Database;
};

#endif // !SQLITEDATABASE_H_
