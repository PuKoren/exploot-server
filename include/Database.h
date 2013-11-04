#pragma once
#include <mysql_driver.h>
#include <cppconn/statement.h>
#include "config.h"

class Database{
public:
    Database();
    ~Database();
    sql::Connection* getConnection();
private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
};