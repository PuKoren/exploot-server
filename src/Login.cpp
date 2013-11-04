#include "Login.h"

Login::Login(sql::Connection* conn){
    con = conn;
}

Login::~Login(){

}

bool Login::Create(const char* uname, const char* upass){
    try{
        sql::PreparedStatement  *prep_stmt;
        prep_stmt = con->prepareStatement("INSERT INTO login(login_name, login_pass) VALUES (?, ?)");
        prep_stmt->setString(1, uname);
        prep_stmt->setString(2, upass);
        if(prep_stmt->execute()){
            std::cout << "User '" << uname << "' created." << std::endl;
            delete prep_stmt;
            return true;
        }else{
            std::cout << "User '" << uname << "' creation failed." << std::endl;
            delete prep_stmt;
            return false;
        }
    }catch(sql::SQLException ex){
        std::cout << "SQL Error: " << ex.getErrorCode() << std::endl;
        return false;
    }
}

bool Login::ProcessMessage(const std::string &str){
    Connect con;
    if(con.ParseFromString(str)){
        return Create(con.nickname().c_str(), con.passhash().c_str());
    }
    return false;
}