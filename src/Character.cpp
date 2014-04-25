#include "Character.h"

Character::Character(sql::Connection *pConn){
    mConn = pConn;
}

Character::~Character(){

}

bool Character::createCharacter(Player *pPlayer, Characters &message, Characters &cbMsg){
    if(message.createdata().char_name().size() == 0) return false;
    if(message.createdata().char_name().size() > 32) return false;

    sql::PreparedStatement  *prep_stmt = NULL;
    sql::ResultSet* res = NULL;

    Characters_CharCreate* creation = cbMsg.mutable_createdata();
    creation->set_char_id(0);
    creation->set_char_name(message.createdata().char_name());
    creation->set_created(false);

    try{
        prep_stmt = mConn->prepareStatement("SELECT character_id FROM characters WHERE character_name = ?");
        prep_stmt->setString(1, message.createdata().char_name());
        res = prep_stmt->executeQuery();
        delete prep_stmt;
        if(res->next()){
            delete res;
            return false;
        }
        delete res;

        prep_stmt = mConn->prepareStatement("INSERT INTO characters(login_id, character_name) VALUES(?, ?)");
        prep_stmt->setInt(1, pPlayer->getId());
        prep_stmt->setString(2, message.createdata().char_name());
        //res = prep_stmt->executeQuery("SELECT mysql_last_insert_id() as id");
        if(prep_stmt->executeUpdate() > 0){
            std::cout << "Character '" << message.createdata().char_name() << "' created." << std::endl;
            delete prep_stmt;
            prep_stmt = mConn->prepareStatement("SELECT LAST_INSERT_ID()");
            res = prep_stmt->executeQuery();
            if(res->next()){
                creation->set_created(true);
                creation->set_char_id(res->getInt("LAST_INSERT_ID()"));
            }
        }else{
            std::cout << "Character " << message.createdata().char_name() << " already exists." << std::endl;
        }

        delete res;
        return true;
    }catch(sql::SQLException ex){
        std::cout << "SQL Error: " << ex.getErrorCode() << std::endl;
    }

    delete res;
    delete prep_stmt;
    return false;
}

void Character::getCharacterList(Player *pPlayer, Characters& message){
    sql::PreparedStatement  *prep_stmt = NULL;
    sql::ResultSet* res = NULL;

    try{
        prep_stmt = mConn->prepareStatement("SELECT character_id, character_name, character_level FROM characters WHERE login_id = ?");
        prep_stmt->setInt(1, pPlayer->getId());
        res =  prep_stmt->executeQuery();

        while(res->next()){
            Characters_CharList* charList = message.add_characterlist();
            charList->set_char_id(res->getInt("character_id"));
            charList->set_char_name(res->getString("character_name"));
            charList->set_char_level(res->getInt("character_level"));
            //result.push_back({res->getInt("character_id"), res->getString("character_name")});
        }

        delete res;
    }catch(sql::SQLException ex){
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
        case Characters::CREATE:
            msg.set_type(Characters::CREATE_CB);
            createCharacter(pPlayer, message, msg);
            data = msg.SerializeAsString();
            break;
        default:
            break;
    }

    return true;
}
