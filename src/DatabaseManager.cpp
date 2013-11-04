#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(){
    std::cout << "Created database manager." << std::endl;
}

DatabaseManager::~DatabaseManager(){
    std::cout << "Destroying database manager." << std::endl;
    delete con;
}

bool DatabaseManager::init(){
    sql::Statement* statement = NULL;
    try{
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(MYSQL_ADDR, MYSQL_USER, MYSQL_PASS);

        std::cout << "Connected to MySQL server: " << MYSQL_ADDR << std::endl;

        statement = con->createStatement();
        statement->execute("USE exploot");
        std::cout << "Selected database: exploot" << std::endl;
        delete statement;
        return true;
    }catch(sql::SQLException ex){
        delete statement;
        if(con){
            delete con;
        }
        con = NULL;
        std::cout << "MySQL Error: " << ex.getErrorCode() << std::endl;
        std::cout << "Failed to initialize DatabaseManager. Check MySQL install or server config.h" << std::endl;
        return false;
    }
}

sql::Connection* DatabaseManager::getConnection(){
    return con;
}
