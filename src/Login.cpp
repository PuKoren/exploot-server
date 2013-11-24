#include "Login.h"

Login::Login(sql::Connection* conn){
    con = conn;
}

Login::~Login(){

}

bool Login::exists(const char* uname){
    sql::PreparedStatement  *prep_stmt = NULL;
    sql::ResultSet* res = NULL;
    bool result = false;
    try{
        prep_stmt = con->prepareStatement("SELECT login_name FROM login WHERE login_name = ?");
        prep_stmt->setString(1, uname);
        res =  prep_stmt->executeQuery();
        
        if(res->next()){
            result = true;
        }

        delete res;
    }catch(sql::SQLException ex){
        std::cout << "SQL Error: " << ex.getErrorCode() << std::endl;
    }

    delete prep_stmt;
    return result;
}

bool Login::create(const char* uname, const char* upass){
    sql::PreparedStatement  *prep_stmt = NULL;
    bool result = false;
    try{
        prep_stmt = con->prepareStatement("INSERT INTO login(login_name, login_pass) VALUES (?, ?)");
        prep_stmt->setString(1, uname);
        prep_stmt->setString(2, hash(upass));
        prep_stmt->execute();
        std::cout << "User '" << uname << "' created." << std::endl;
        result = true;
    }catch(sql::SQLException ex){
        std::cout << "User '" << uname << "' creation failed: ";
        std::cout << "SQL Error: " << ex.getErrorCode() << std::endl;
    }
    delete prep_stmt;
    return result;
}

bool Login::login(const char* uname,  const char* upass, std::string uchallenge){
    sql::PreparedStatement  *prep_stmt = NULL;
    sql::ResultSet* res = NULL;
    bool result = false;
    try{
        prep_stmt = con->prepareStatement("SELECT login_pass FROM login WHERE login_name = ?");
        prep_stmt->setString(1, uname);
        res =  prep_stmt->executeQuery();
        if(res->next()){
            std::string retrievedPassword = res->getString("login_pass"); // also, should handle case where Password length > PASSWORD_LENGTH
            retrievedPassword.append(uchallenge);

            if(md5(retrievedPassword).compare(upass) == 0){
                result = true;
                std::cout << "User '" << uname << "' logged in." << std::endl;
            }else{
                result = false;
                std::cout << "User '" << uname << "' failed to log in: Bad password." << std::endl;
            }
        }else{
            std::cout << "User '" << uname << "' failed to log in: User not found." << std::endl;
        }
        delete res;
    }catch(sql::SQLException ex){
        std::cout << "SQL Error: " << ex.getErrorCode() << std::endl;
    }

    delete prep_stmt;
    return result;
}

bool Login::processMessage(const std::string &str, std::string challenge){
    Connect con;
    bool result = false;
    if(con.ParseFromString(str)){
        /*if(!exists(con.nickname().c_str())){
            result = create(con.nickname().c_str(), con.passhash().c_str());
        }else{*/
        result = login(con.nickname().c_str(), con.passhash().c_str(), challenge);
        //}
    }else{
        std::cout << "Bad protobuf received" << std::endl;
    }
    return result;
}
