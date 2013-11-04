#pragma once
#include <mysql_driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class Login{
public:
    Login(sql::Connection*);
    ~Login();
    bool Create(const char* uname, const char* upass);
private:
    sql::Connection *con;
};