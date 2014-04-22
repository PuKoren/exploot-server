#include "MessageManager.h"

MessageManager::MessageManager(DatabaseManager* db){
    dbManager = db;
    login = NULL;
}

MessageManager::~MessageManager(){
    delete login;
}

bool MessageManager::init(){
    login = new Login(dbManager->getConnection());
    return true;
}

bool MessageManager::ProcessMessage(Message& msg, ENetPeer* peer, Message::MessageType &type, std::string& data){
    bool result = false;

    if(msg.message().size() > 0){
        Message::MessageData msgData = msg.message().Get(0);
        if(msgData.type() == Message::CONNECT){
			ConnectCallback cb;
			cb.set_succeed(login->processMessage(msgData.data(), peer));
			result = true;
			type = Message::LOGIN_CALLBACK;
			data = cb.SerializeAsString();
        }else{
            std::cout << "Message type not handled yet." << std::endl;
        }
    }else{
        std::cout << "Not enough parameters" << std::endl;
    }

    return result;
}
