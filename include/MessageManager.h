#pragma once
#include <enet/enet.h>
#include "exploot-protobuf/build/Message.pb.h"
#include "exploot-protobuf/build/Connect.pb.h"
#include "exploot-protobuf/build/Connect.callback.pb.h"
#include "Login.h"
#include "Character.h"
#include "DatabaseManager.h"

/**
* Network Manager
* Manage messages between client and server
* 
**/
class MessageManager{
public:
    MessageManager(DatabaseManager*);
    ~MessageManager();

	/*
	* ProcessMessage will analyse the packet data and transmit it to message manager
	* It disconnect clients and connects with them, sending a challenge hash when user firstly connects
	* @return_value (string) is filled with data if some info must be sent back to user
	* @return_type (Message_MessageType) contains the protobuf type returned
	* returns true or false (true => message in return_value must be sent back to user)
	*/
    bool ProcessMessage(Message&, ENetPeer* peer, Message::MessageType &type, std::string &data);
    bool init();
private:
    DatabaseManager* dbManager;
    Login* login;
    Character* mChar;
};
