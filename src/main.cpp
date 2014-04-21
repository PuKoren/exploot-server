#include <iostream>
#include <signal.h>
#include "DatabaseManager.h"
#include "MessageManager.h"
#include "NetworkManager.h"

static bool keepRunning = true;
void intHandler(int dummy = 0) {
    keepRunning = false;
}

int main(int argc, char** argv){
	signal(SIGINT, intHandler);

	std::cout << "Launching managers..." << std::endl;

    DatabaseManager* dbManager = new DatabaseManager();
    MessageManager* msgManager = new MessageManager(dbManager);
    NetworkManager* netManager = new NetworkManager(msgManager);

    if(dbManager->init() && netManager->init() && msgManager->init()){
		std::cout << "Managers launched !" << std::endl;
        std::cout << "Press CTRL+C to exit" << std::endl;
        while(keepRunning){
            netManager->update();
        }
    }

	std::cout << "End signal received." << std::endl;
	std::cout << "Destroying managers..." << std::endl;

    delete netManager;
    delete msgManager;
    delete dbManager;

	std::cout << "Managers destroyed." << std::endl;
	return 0;
}
