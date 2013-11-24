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

bool MessageManager::ProcessMessage(Message& msg, ENetPeer* peer){
    bool result = false;

    if(msg.message().size() > 0){
        Message::MessageData msgData = msg.message().Get(0);
        if(msgData.type() == Message::CONNECT){
            result = login->processMessage(msgData.data(), *((std::string*)peer->data));
        }else{
            std::cout << "Message type not handled yet." << std::endl;
        }
    }else{
        std::cout << "Not enough parameters" << std::endl;
    }

    return result;
}
