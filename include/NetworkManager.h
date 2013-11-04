#pragma once
#include <iostream>
#include <enet/enet.h>
#include "config.h"
#include "MessageManager.h"
#include "exploot-protobuf/build/Message.pb.h"

using namespace std;

class NetworkManager{
public:
    NetworkManager(MessageManager*);
    ~NetworkManager();
    void update();
    bool init();
private:
    ENetHost * server;
    MessageManager* msgManager;
};