#pragma once
#include <iostream>
#include <vector>
#include <enet/enet.h>
#include <sstream>
#include "md5.h"
#include "config.h"
#include "MessageManager.h"
#include "exploot-protobuf/build/Message.pb.h"

using namespace std;

class NetworkManager{
public:
    NetworkManager(MessageManager*);
    ~NetworkManager();
    void sendMessage(ENetPeer* peer, Message& message);
    string getChallenge(int connectID);
    void update();
    bool init();
private:
    ENetHost * server;
    MessageManager* msgManager;
};
