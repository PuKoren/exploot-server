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
    DatabaseManager* dbManager = new DatabaseManager();
    MessageManager* msgManager = new MessageManager(dbManager);
    NetworkManager* netManager = new NetworkManager(msgManager);
    signal(SIGINT, intHandler);

    if(dbManager->init() && netManager->init() && msgManager->init()){
        std::cout << "Press CTRL+C to exit" << std::endl;
        while(keepRunning){
            netManager->update();
        }
    }

    delete netManager;
    delete msgManager;
    delete dbManager;

	return 0;
}
