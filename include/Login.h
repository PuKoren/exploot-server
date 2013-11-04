#pragma once
#include <string>
#include <mysql_driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include "exploot-protobuf/build/Connect.pb.h"

class Login{
public:
    Login(sql::Connection*);
    ~Login();
    bool Create(const char* uname, const char* upass);
    bool ProcessMessage(const std::string &str);
private:
    sql::Connection *con;
};