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

bool MessageManager::ProcessMessage(Message& msg){
    if(msg.message().size() > 0){
        Message::MessageData msgData = msg.message().Get(0);
        if(msgData.type() == Message::CONNECT){
            return login->ProcessMessage(msgData.data());
        }else{
            std::cout << "Message type not handled yet." << std::endl;
        }
    }else{
        std::cout << "Not enough parameters" << std::endl;
    }

    return false;
}
