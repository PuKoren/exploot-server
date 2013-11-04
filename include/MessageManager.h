#pragma once
#include "exploot-protobuf/build/Message.pb.h"
#include "exploot-protobuf/build/Connect.pb.h"
#include "Login.h"
#include "DatabaseManager.h"

class MessageManager{
public:
    MessageManager(DatabaseManager*);
    ~MessageManager();
    bool ProcessMessage(Message&);
    bool init();
private:
    DatabaseManager* dbManager;
    Login* login;
};