#include "Login.h"

Login::Login(sql::Connection* conn){
    con = conn;
}

Login::~Login(){

}

bool Login::Create(const char* uname, const char* upass){
    sql::PreparedStatement  *prep_stmt;
    prep_stmt = con->prepareStatement("INSERT INTO login(login_name, login_pass) VALUES (?, ?)");
    prep_stmt->setString(1, uname);
    prep_stmt->setString(2, upass);
    bool result = prep_stmt->execute();
    delete prep_stmt;
    return result;
}