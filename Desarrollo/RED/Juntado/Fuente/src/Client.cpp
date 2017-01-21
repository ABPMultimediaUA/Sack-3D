#include "Client.h"
#include "PhysicWorld.h"

Client::Client()
{
    //ctor
    //unsigned char GetPacketIdentifier(RakNet::Packet *p);
    client=RakNet::RakPeerInterface::GetInstance();
    clientID=RakNet::UNASSIGNED_SYSTEM_ADDRESS;
    isServer=false;
}

void Client::iniciar(){
    RakNet::SocketDescriptor socketDescriptor(atoi(PhysicWorld::Instance()->getPlayer()->getClientPort()),0);
	socketDescriptor.socketFamily=AF_INET;
	client->Startup(8,&socketDescriptor, 1);
	client->SetOccasionalPing(true);

	#if LIBCAT_SECURITY==1
        char public_key[cat::EasyHandshake::PUBLIC_KEY_BYTES];
        FILE *fp = fopen("publicKey.dat","rb");
        fread(public_key,sizeof(public_key),1,fp);
        fclose(fp);
    #endif

    #if LIBCAT_SECURITY==1
        RakNet::PublicKey pk;
        pk.remoteServerPublicKey=public_key;
        pk.publicKeyMode=RakNet::PKM_USE_KNOWN_PUBLIC_KEY;
        bool b = client->Connect(PhysicWorld::Instance()->getPlayer()->getIp(), atoi(PhysicWorld::Instance()->getPlayer()->getServerPort()), "Rumpelstiltskin", (int) strlen("Rumpelstiltskin"), &pk)==RakNet::CONNECTION_ATTEMPT_STARTED;
    #else
	RakNet::ConnectionAttemptResult car = client->Connect(PhysicWorld::Instance()->getPlayer()->getIp(), atoi(PhysicWorld::Instance()->getPlayer()->getServerPort()), "Rumpelstiltskin", (int) strlen("Rumpelstiltskin"));
	RakAssert(car==RakNet::CONNECTION_ATTEMPT_STARTED);
    #endif

	printf("\nMy IP addresses:\n");
	unsigned int i;
	for (i=0; i < client->GetNumberOfAddresses(); i++)
	{
		printf("%i. %s\n", i+1, client->GetLocalIP(i));
	}

	printf("My GUID is %s\n", client->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString());
	puts("'quit' to quit. 'stat' to show stats. 'ping' to ping.\n'disconnect' to disconnect. 'connect' to reconnnect. Type to talk.");


    /*while(1){
        /* --------MENSAJES SOBRE CONEXION ---------
        for (p=client->Receive(); p; client->DeallocatePacket(p), p=client->Receive())
            {
            // We got a packet, get the identifier with our handy function
            packetIdentifier = GetPacketIdentifier(p);

            // Check if this is a network message packet
            switch (packetIdentifier)
            {
            case ID_DISCONNECTION_NOTIFICATION:
                // Connection lost normally
                printf("ID_DISCONNECTION_NOTIFICATION\n");
                break;
            case ID_ALREADY_CONNECTED:
                // Connection lost normally
                printf("ID_ALREADY_CONNECTED\n");
                break;
            case ID_INCOMPATIBLE_PROTOCOL_VERSION:
                printf("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
                break;
            case ID_REMOTE_DISCONNECTION_NOTIFICATION: // Server telling the clients of another client disconnecting gracefully.  You can manually broadcast this in a peer to peer enviroment if you want.
                printf("ID_REMOTE_DISCONNECTION_NOTIFICATION\n");
                break;
            case ID_REMOTE_CONNECTION_LOST: // Server telling the clients of another client disconnecting forcefully.  You can manually broadcast this in a peer to peer enviroment if you want.
                printf("ID_REMOTE_CONNECTION_LOST\n");
                break;
            case ID_REMOTE_NEW_INCOMING_CONNECTION: // Server telling the clients of another client connecting.  You can manually broadcast this in a peer to peer enviroment if you want.
                printf("ID_REMOTE_NEW_INCOMING_CONNECTION\n");
                break;
            case ID_CONNECTION_BANNED: // Banned from this server
                printf("We are banned from this server.\n");
                break;
            case ID_CONNECTION_ATTEMPT_FAILED:
                printf("Connection attempt failed\n");
                break;
            case ID_NO_FREE_INCOMING_CONNECTIONS:
                // Sorry, the server is full.  I don't do anything here but
                // A real app should tell the user
                printf("ID_NO_FREE_INCOMING_CONNECTIONS\n");
                break;

            case ID_INVALID_PASSWORD:
                printf("ID_INVALID_PASSWORD\n");
                break;

            case ID_CONNECTION_LOST:
                // Couldn't deliver a reliable packet - i.e. the other system was abnormally
                // terminated
                printf("ID_CONNECTION_LOST\n");
                break;

            case ID_CONNECTION_REQUEST_ACCEPTED:
                // This tells the client they have connected
                printf("ID_CONNECTION_REQUEST_ACCEPTED to %s with GUID %s\n", p->systemAddress.ToString(true), p->guid.ToString());
                printf("My external address is %s\n", client->GetExternalID(p->systemAddress).ToString(true));
                break;
            default:
                // It's a client, so just show the message
                printf("%s\n", p->data);
                break;
            }
        }
    }*/

}

unsigned char Client::GetPacketIdentifier(RakNet::Packet *p)
{
	if (p==0)
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	}
	else
		return (unsigned char) p->data[0];
}

Client::~Client()
{
    //dtor
}
