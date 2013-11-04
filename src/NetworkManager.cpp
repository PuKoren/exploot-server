#include "NetworkManager.h"

NetworkManager::NetworkManager(MessageManager* msg){
    msgManager = msg;
    std::cout << "Created network manager." << std::endl;
}

NetworkManager::~NetworkManager(){
    std::cout << "Destroying network manager." << std::endl;
    enet_host_destroy(server);
    enet_deinitialize();
}

bool NetworkManager::init(){
    if (enet_initialize () != 0){
        cout << "An error occurred while initializing ENet." << endl;
        return false;
    }
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = UDP_PORT;
    server = enet_host_create (& address /* the address to bind the server host to */,
                                 32      /* allow up to 32 clients and/or outgoing connections */,
                                  2      /* allow up to 2 channels to be used, 0 and 1 */,
                                  0      /* assume any amount of incoming bandwidth */,
                                  0      /* assume any amount of outgoing bandwidth */);
    if (server == NULL){
        cout << "An error occurred while trying to create an ENet server host." << endl;
        return false;
    }

    std::cout << "Server listening on port: " << UDP_PORT << std::endl;
    return true;
}

void NetworkManager::update(){
    ENetEvent event;
    while (enet_host_service (server, &event, 10) >= 0)
    { 
        if(event.type == ENET_EVENT_TYPE_CONNECT){
            cout << "A new client connected from " << event.peer->address.host << ":" << event.peer -> address.port << endl;
        }else if(event.type == ENET_EVENT_TYPE_RECEIVE){
            Message msg;
            msg.ParseFromString((char*)event.packet->data);
            if(msg.message().size() > 0){
                msgManager->ProcessMessage(msg);
            }
            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy (event.packet);
        }else if(event.type == ENET_EVENT_TYPE_DISCONNECT){
            cout << event.peer->address.host << " disconected." << endl;
            /* Reset the peer's client information. */
            event.peer->data = NULL;
        }
    }
}