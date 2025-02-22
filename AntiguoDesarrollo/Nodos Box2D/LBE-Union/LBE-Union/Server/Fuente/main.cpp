#include "MessageIdentifiers.h"
#include <iostream>
#include <vector>
#include <time.h>
#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include "RakNetTypes.h"
#include "BitStream.h"
#include "RakSleep.h"
#include "PacketLogger.h"
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#ifdef _WIN32
#include "Kbhit.h"
#endif
#include <stdio.h>
#include <string.h>
#include "Gets.h"
#include <stdlib.h>
#if LIBCAT_SECURITY==1
#include "SecureHandshake.h" // Include header for secure handshake
#endif

#if defined(_CONSOLE_2)
#include "Console2SampleIncludes.h"
#endif

// We copy this from Multiplayer.cpp to keep things all in one file for this example
unsigned char GetPacketIdentifier(RakNet::Packet *p);
std::vector<int> listaMapas();


#ifdef _CONSOLE_2
_CONSOLE_2_SetSystemProcessParams
#endif


int main(void){
    std::vector<int> maps;
    maps = listaMapas();
	// Pointers to the interfaces of our server and client.
	// Note we can easily have both in the same program
	RakNet::RakPeerInterface *server=RakNet::RakPeerInterface::GetInstance();
	//RM3sys replicaManager;
  //  FullyConnectedMesh2 *fullyConnectedMesh;
   // ConnectionGraph2 *connectionGraph;
	RakNet::RakNetStatistics *rss;
//	NetworkIDManager networkIdManager;
	server->SetIncomingPassword("Rumpelstiltskin", (int)strlen("Rumpelstiltskin"));
	server->SetTimeoutTime(30000,RakNet::UNASSIGNED_SYSTEM_ADDRESS);
//	RakNet::PacketLogger packetLogger;
//	server->AttachPlugin(&packetLogger);

#if LIBCAT_SECURITY==1
	cat::EasyHandshake handshake;
	char public_key[cat::EasyHandshake::PUBLIC_KEY_BYTES];
	char private_key[cat::EasyHandshake::PRIVATE_KEY_BYTES];
	handshake.GenerateServerKey(public_key, private_key);
	server->InitializeSecurity(public_key, private_key, false);
	FILE *fp = fopen("publicKey.dat","wb");
	fwrite(public_key,sizeof(public_key),1,fp);
	fclose(fp);
#endif

	// Holds packets
	RakNet::Packet* p;

	// GetPacketIdentifier returns this
	unsigned char packetIdentifier;

	// Record the first client that connects to us so we can pass it to the ping function
	RakNet::SystemAddress clientID=RakNet::UNASSIGNED_SYSTEM_ADDRESS;
	int clID = 0;

	// Holds user data
	char portstring[30];

	printf("This is a sample implementation of a text based chat server.\n");
	printf("Connect to the project 'Chat Example Client'.\n");
	printf("Difficulty: Beginner\n\n");

	// A server
	puts("Enter the server port to listen on");
	//Gets(portstring,sizeof(portstring));
	strncpy(portstring, "3333", sizeof(portstring));
	if (portstring[0]==0)
		strcpy(portstring, "1234");

	puts("Starting server.");
	// Starting the server is very simple.  2 players allowed.
	// 0 means we don't care about a connectionValidationInteger, and false
	// for low priority threads
	// I am creating two socketDesciptors, to create two sockets. One using IPV6 and the other IPV4
	RakNet::SocketDescriptor socketDescriptors[2];
	socketDescriptors[0].port=atoi(portstring);
	socketDescriptors[0].socketFamily=AF_INET; // Test out IPV4
	socketDescriptors[1].port=atoi(portstring);
	socketDescriptors[1].socketFamily=AF_INET6; // Test out IPV6

	bool b = server->Startup(4, socketDescriptors, 2 )==RakNet::RAKNET_STARTED;

	//server->AttachPlugin(&replicaManager);
	//server->AttachPlugin(fullyConnectedMesh);
	//server->AttachPlugin(connectionGraph);
	//replicaManager.SetNetworkIDManager(&networkIdManager);

	server->SetMaximumIncomingConnections(4);
	if (!b){
		printf("Failed to start dual IPV4 and IPV6 ports. Trying IPV4 only.\n");

		// Try again, but leave out IPV6
		b = server->Startup(4, socketDescriptors, 1 )==RakNet::RAKNET_STARTED;
		if (!b){
			puts("Server failed to start.  Terminating.");
			exit(1);
		}
	}
	server->SetOccasionalPing(true);
	server->SetUnreliableTimeout(1000);

	DataStructures::List<RakNet::RakNetSmartPtr < RakNet::RakNetSocket> > sockets;
	server->GetSockets(sockets);
	printf("Socket addresses used by RakNet:\n");
	for (unsigned int i=0; i < sockets.Size(); i++){
		printf("%i. %s\n", i+1, sockets[i]->boundAddress.ToString(true));
	}

	printf("\nMy IP addresses:\n");
	for (unsigned int i=0; i < server->GetNumberOfAddresses(); i++){
		printf("%i. %s\n", i+1, server->GetLocalIP(i));
	}

	printf("\nMy GUID is %s\n", server->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString());
	puts("'quit' to quit. 'stat' to show stats. 'ping' to ping.\n'ban' to ban an IP from connecting.\n'kick to kick the first connected player.\nType to talk.");
	char message[2048];

	// Loop for input
	while (1){

	// This sleep keeps RakNet responsive
	RakSleep(30);

	if (kbhit()){
		// Notice what is not here: something to keep our network running.  It's
		// fine to block on gets or anything we want
		// Because the network engine was painstakingly written using threads.
		Gets(message,sizeof(message));
		if (strcmp(message, "quit")==0){
			puts("Quitting.");
			break;
		}
		if (strcmp(message, "stat")==0){
			rss=server->GetStatistics(server->GetSystemAddressFromIndex(0));
			StatisticsToString(rss, message, 2);
			printf("%s", message);
			printf("Ping %i\n", server->GetAveragePing(server->GetSystemAddressFromIndex(0)));

			continue;
		}
		if (strcmp(message, "ping")==0){
			server->Ping(clientID);

			continue;
		}
		if (strcmp(message, "getconnectionlist")==0){
			RakNet::SystemAddress systems[10];
			unsigned short numConnections=10;
			server->GetConnectionList((RakNet::SystemAddress*) &systems, &numConnections);
			for (int i=0; i < numConnections; i++)
			{
				printf("%i. %s\n", i+1, systems[i].ToString(true));
			}
			continue;
		}
		// Message now holds what we want to broadcast
		char message2[2048];
		// Append Server: to the message so clients know that it ORIGINATED from the server
		// All messages to all clients come from the server either directly or by being
		// relayed from other clients
		message2[0]=0;
		//strcpy(message2, "6 ");
		sprintf(message2, "6 %.0f %.0f %.0f %.0f %.0f %.0f", (float)maps[0], (float)maps[1], (float)maps[2], (float)maps[3], (float)maps[4], (float)maps[5]);
		strcat(message2, message);

		// message2 is the data to send
		// strlen(message2)+1 is to send the null terminator
		// HIGH_PRIORITY doesn't actually matter here because we don't use any other priority
		// RELIABLE_ORDERED means make sure the message arrives in the right order
		// We arbitrarily pick 0 for the ordering stream
		// RakNet::UNASSIGNED_SYSTEM_ADDRESS means don't exclude anyone from the broadcast
		// true means broadcast the message to everyone connected
		server->Send(message2, (const int) strlen(message2)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
	}

		// Get a packet from either the server or the client

		for (p=server->Receive(); p; server->DeallocatePacket(p), p=server->Receive()){
			// We got a packet, get the identifier with our handy function
			packetIdentifier = GetPacketIdentifier(p);

			// Check if this is a network message packet
			switch (packetIdentifier){
			case ID_DISCONNECTION_NOTIFICATION:
				// Connection lost normally
				printf("ID_DISCONNECTION_NOTIFICATION from %s\n", p->systemAddress.ToString(true));;
				break;


			case ID_NEW_INCOMING_CONNECTION:
				// Somebody connected.  We have their IP now
				char identificador[30];
				char playerNum[30];
				printf("ID_NEW_INCOMING_CONNECTION from %s with GUID %s\n", p->systemAddress.ToString(true), p->guid.ToString());
				strncpy(identificador, "0", sizeof(identificador));
				strncpy(playerNum, "", sizeof(playerNum));
				clientID=p->systemAddress; // Record the player ID of the client
				for(int i=clID; i>=0; i--){
                    sprintf(playerNum, "%.0f", (float)i);
                    strncat (identificador, " ", 30);
                    strncat (identificador, playerNum, 30);
				}
				clID++;
                //enviando ID al jugador conectado
                server->Send(identificador, (const int) strlen(identificador)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
                //strncpy(identificador, "", sizeof(identificador));
				break;

			case ID_INCOMPATIBLE_PROTOCOL_VERSION:
				printf("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
				break;


			case ID_CONNECTION_LOST:
				// Couldn't deliver a reliable packet - i.e. the other system was abnormally
				// terminated
				printf("ID_CONNECTION_LOST from %s\n", p->systemAddress.ToString(true));;
				break;

			default:
				// The server knows the static data of all clients, so we can prefix the message
				// With the name data
				//printf("%s\n", p->data);

				// Relay the message.  We prefix the name for other clients.  This demonstrates
				// That messages can be changed on the server before being broadcast
				// Sending is the same as before
				sprintf(message, "%s", p->data);
				server->Send(message, (const int) strlen(message)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, p->systemAddress, true);

				break;
			}

		}
	}

	server->Shutdown(300);
	// We're done with the network
	RakNet::RakPeerInterface::DestroyInstance(server);

	return 0;
}

// Copied from Multiplayer.cpp
// If the first byte is ID_TIMESTAMP, then we want the 5th byte
// Otherwise we want the 1st byte
unsigned char GetPacketIdentifier(RakNet::Packet *p){
	if (p==0)
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP){
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	}
	else
		return (unsigned char) p->data[0];
}

std::vector<int> listaMapas(){
    time_t timer;
    time(&timer);
    srand (timer);
    int x=0;
    std::vector<int> nums;
    std::vector<int> result;

    for(int i=0;i<6;i++) nums.push_back(i);
std::cout<<" sddfdfd"<<std::endl;
    while(nums.size()!=0){
        x = rand() % nums.size();
        result.push_back(nums[x]);
        nums.erase(nums.begin()+x);
    }
    std::cout<<result[0]<<" "<<result[1]<<" "<<result[2]<<" "<<result[3]<<" "<<result[4]<<" "<<result[5]<<" "<<std::endl;
    return result;

}


