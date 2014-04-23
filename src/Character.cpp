#include "Character.h"

Character::Character(sql::Connection *pConn){
    mConn = pConn;
}

Character::~Character(){

}

void Character::getCharacterList(Player *pPlayer, Characters& message){
    sql::PreparedStatement  *prep_stmt = NULL;
    sql::ResultSet* res = NULL;

    try{
        prep_stmt = mConn->prepareStatement("SELECT character_id, character_name, character_level FROM characters WHERE login_id = ?");
        prep_stmt->setInt(1, pPlayer->getId());
        res =  prep_stmt->executeQuery();

        if(res->next()){
            Characters_CharList* charList = message.add_characterlist();
            charList->set_char_id(res->getInt("character_id"));
            charList->set_char_name(res->getString("character_name"));
            charList->set_char_level(res->getInt("character_level"));
            //result.push_back({res->getInt("character_id"), res->getString("character_name")});
        }

        delete res;
    }catch(sql::SQLException ex){
        if(prep_stmt) delete prep_stmt;
        std::cout << "SQL Error: " << ex.getErrorCode() << std::endl;
    }

    delete prep_stmt;
}

bool Character::processMessage(const std::string &str, Player *pPlayer, std::string &data){
    Characters message;
    message.ParseFromString(str);

    Characters msg;
    switch(message.type()){
        case Characters::LIST:
            msg.set_type(Characters::LIST_CB);
            getCharacterList(pPlayer, msg);
            data = msg.SerializeAsString();
            break;
    }

    return true;
}
