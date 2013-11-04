#include <iostream>
#include <enet/enet.h>
#include "exploot-protobuf/build/Message.pb.h"
#include "exploot-protobuf/build/Connect.pb.h"
#include "config.h"
#include "Database.h"
#include "Login.h"

using namespace std;

int main(int argc, char** argv){
    if (enet_initialize () != 0){
        cout << "An error occurred while initializing ENet." << endl;
        return EXIT_FAILURE;
    }
    ENetAddress address;
    ENetHost * server;
    address.host = ENET_HOST_ANY;
    address.port = UDP_PORT;
    server = enet_host_create (& address /* the address to bind the server host to */,
                                 32      /* allow up to 32 clients and/or outgoing connections */,
                                  2      /* allow up to 2 channels to be used, 0 and 1 */,
                                  0      /* assume any amount of incoming bandwidth */,
                                  0      /* assume any amount of outgoing bandwidth */);
    if (server == NULL){
        cout << "An error occurred while trying to create an ENet server host." << endl;
        exit (EXIT_FAILURE);
    }

    std::cout << "Listening on port " << UDP_PORT << "..." << std::endl;
    ENetEvent event;
    Database db;
    /* Wait up to 1000 milliseconds for an event. */
    while (enet_host_service (server, &event, 1000) >= 0)
    {
        
        if(event.type == ENET_EVENT_TYPE_CONNECT){
            cout << "A new client connected from " << event.peer->address.host << ":" << event.peer -> address.port << endl;
        }else if(event.type == ENET_EVENT_TYPE_RECEIVE){
            Message msg;
            msg.ParseFromString((char*)event.packet->data);
            if(msg.message().size() > 0){
                Message::MessageData msgData = msg.message().Get(0);
                if(msgData.type() == Message::CONNECT){
                    Connect con;
                    if(con.ParseFromString(msgData.data())){
                        std::cout << "User " << con.nickname() << " tries to log in with password " << con.passhash() << std::endl; 
                        Login log(db.getConnection());
                        log.Create(con.nickname().c_str(), con.passhash().c_str());
                    }else{
                        std::cout << "Invalid message data string" << std::endl;
                    }
                }else{
                    std::cout << "Message type not handled yet." << std::endl;
                }
            }else{
                std::cout << "Not enough parameters" << std::endl;
            }
            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy (event.packet);
        }else if(event.type == ENET_EVENT_TYPE_DISCONNECT){
            cout << event.peer->address.host << " disconected." << endl;
            /* Reset the peer's client information. */
            event.peer->data = NULL;
        }
    }

    enet_host_destroy(server);
    enet_deinitialize();
	return 0;
}
