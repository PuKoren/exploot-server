#pragma once
#include <iostream>
#include <mysql_driver.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include "config.h"

class DatabaseManager{
public:
    DatabaseManager();
    ~DatabaseManager();
    sql::Connection* getConnection();
    bool init();
private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
};