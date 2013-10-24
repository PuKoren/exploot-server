#include <iostream>
#include <enet/enet.h>
#include "config.h"

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
    ENetEvent event;
    /* Wait up to 1000 milliseconds for an event. */
    while (enet_host_service (server, & event, 1000) >= 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            cout << "A new client connected from "
                 << event.peer->address.host << ":"
                 << event.peer -> address.port << endl;
            /* Store any relevant client information here. */
            //event.peer->data = "Client information";
            break;
        case ENET_EVENT_TYPE_RECEIVE:
            cout << "A packet of length "<< event.packet -> dataLength << " containing "
                 << event.packet->data << " was received from "
                 << event.peer->data << " on channel "
                 << event.channelID << endl;
            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy (event.packet);

            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            cout << event.peer -> data << " disconected." << endl;
            /* Reset the peer's client information. */
            event.peer -> data = NULL;
        }
    }

    enet_host_destroy(server);
    enet_deinitialize();
	return 0;
}
