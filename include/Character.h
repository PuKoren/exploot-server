#pragma once
#include <vector>
#include <string>
#include <mysql_driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include "md5.h"
#include "Player.h"
#include "exploot-protobuf/build/Characters.pb.h"

struct chara{
    int char_id;
    std::string char_name;
};

class Character{
public:
    Character(sql::Connection* pConn);
    ~Character();

    void getCharacterList(Player* pPlayer, Characters& message);
    bool processMessage(const std::string &str, Player* pPlayer, std::string &data);
private:
    sql::Connection *mConn;
};
