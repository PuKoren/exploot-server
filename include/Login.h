#pragma once
#include <string>
#include <enet/enet.h>
#include <mysql_driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include "md5.h"
#include "exploot-protobuf/build/Connect.pb.h"

class Login{
public:
    Login(sql::Connection*);
    ~Login();
    bool create(const char* uname, const char* upass);
    bool login(const char* uname, const char* upass, ENetPeer* uhash);
    bool processMessage(const std::string &str, ENetPeer* peer);
private:
    sql::Connection *con;
    bool exists(const char* uname);
};
