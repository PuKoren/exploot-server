#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(){
	con = NULL;
	driver = NULL;
}

DatabaseManager::~DatabaseManager(){
	if(con) con->close();
	delete con;
}

bool DatabaseManager::init(){
    sql::Statement* statement = NULL;
    try{
        driver = sql::mysql::get_mysql_driver_instance();
		if(driver == NULL) throw sql::SQLException("Null driver instance returned.");
        con = driver->connect(MYSQL_ADDR, MYSQL_USER, MYSQL_PASS);

        std::cout << "Connected to MySQL server: " << MYSQL_ADDR << std::endl;

        statement = con->createStatement();
        statement->execute("USE exploot");
        std::cout << "Selected database: exploot" << std::endl;
        delete statement;
        return true;
    }catch(sql::SQLException& ex){
		std::cout << "MySQL Error: " << ex.getErrorCode() << std::endl;
        std::cout << "Failed to initialize DatabaseManager. Check MySQL install or server config.h" << std::endl;
        delete statement;
        return false;
    }
}

sql::Connection* DatabaseManager::getConnection(){
    return con;
}
