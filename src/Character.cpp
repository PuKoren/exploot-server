#include "Character.h"

Character::Character(sql::Connection *pConn){
    mConn = pConn;
}

Character::~Character(){

}

std::vector<chara> Character::getCharacterList(Player *pPlayer){
    sql::PreparedStatement  *prep_stmt = NULL;
    sql::ResultSet* res = NULL;
    std::vector<chara> result;

    try{
        prep_stmt = mConn->prepareStatement("SELECT character_id, character_name FROM characters WHERE login_id = ?");
        prep_stmt->setInt(1, pPlayer->getId());
        res =  prep_stmt->executeQuery();

        if(res->next()){
            result.push_back({res->getInt("character_id"), res->getString("character_name")});
        }

        delete res;
    }catch(sql::SQLException ex){
        if(prep_stmt) delete prep_stmt;
        std::cout << "SQL Error: " << ex.getErrorCode() << std::endl;
    }

    delete prep_stmt;
    return result;
}

bool Character::processMessage(const std::string &str, Player *pPlayer, std::string &data){
    Characters message;
    message.ParseFromString(str);

    switch(message.type()){
        case Characters::LIST:
            //std::vector<chara> char_list = getCharacterList(pPlayer);
            data = "";
            break;
        default:
            data = "";
            break;
    }

    return true;
}
