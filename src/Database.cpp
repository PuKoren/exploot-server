#include "Database.h"

Database::Database(){
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect(MYSQL_ADDR, MYSQL_USER, MYSQL_PASS);

    sql::Statement* statement = con->createStatement();
    statement->execute("USE exploot");
    delete statement;
}

Database::~Database(){
    delete con;
}

sql::Connection* Database::getConnection(){
    return con;
}