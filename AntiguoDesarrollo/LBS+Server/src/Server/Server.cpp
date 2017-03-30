#include "Server/Server.h"

#include "MessageIdentifiers.h"
#include <iostream>
#include <time.h>
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



Server::Server():m_started(false),clID(0){
    m_maps = listaMapas();
	m_server=RakNet::RakPeerInterface::GetInstance();
	m_server->SetIncomingPassword("Rumpelstiltskin", (int)strlen("Rumpelstiltskin"));
	m_server->SetTimeoutTime(30000,RakNet::UNASSIGNED_SYSTEM_ADDRESS);
	timer2Start = IrrMngr::Inst()->getTimer();
	time2Start = timer2Start->getTime();
	#if LIBCAT_SECURITY==1
		cat::EasyHandshake handshake;
		char public_key[cat::EasyHandshake::PUBLIC_KEY_BYTES];
		char private_key[cat::EasyHandshake::PRIVATE_KEY_BYTES];
		handshake.GenerateServerKey(public_key, private_key);
		m_server->InitializeSecurity(public_key, private_key, false);
		FILE *fp = fopen("publicKey.dat","wb");
		fwrite(public_key,sizeof(public_key),1,fp);
		fclose(fp);
	#endif

	char portstring[30];
	printf("This is a sample implementation of a text based chat server.\n");
	puts("Enter the server port to listen on");
	//Gets(portstring,sizeof(portstring));
	strncpy(portstring, "3333", sizeof(portstring));
	if (portstring[0]==0)
		strcpy(portstring, "1234");

	puts("Starting server.");
	RakNet::SocketDescriptor socketDescriptors[2];
	socketDescriptors[0].port=atoi(portstring);
	socketDescriptors[0].socketFamily=AF_INET; // Test out IPV4
	socketDescriptors[1].port=atoi(portstring);
	socketDescriptors[1].socketFamily=AF_INET6; // Test out IPV6

	bool b = m_server->Startup(4, socketDescriptors, 2 )==RakNet::RAKNET_STARTED;

	//server->AttachPlugin(&replicaManager);
	//server->AttachPlugin(fullyConnectedMesh);
	//server->AttachPlugin(connectionGraph);
	//replicaManager.SetNetworkIDManager(&networkIdManager);

	m_server->SetMaximumIncomingConnections(4);
	if (!b){
		printf("Failed to start dual IPV4 and IPV6 ports. Trying IPV4 only.\n");
		b = m_server->Startup(4, socketDescriptors, 1 )==RakNet::RAKNET_STARTED;
		if (!b){
			puts("Server failed to start.  Terminating.");
			exit(1);
		}
	}
	m_server->SetOccasionalPing(true);
	m_server->SetUnreliableTimeout(1000);

	DataStructures::List<RakNet::RakNetSmartPtr < RakNet::RakNetSocket> > sockets;
	m_server->GetSockets(sockets);
	printf("Socket addresses used by RakNet:\n");
	for (unsigned int i=0; i < sockets.Size(); i++){
		printf("%i. %s\n", i+1, sockets[i]->boundAddress.ToString(true));
	}

	printf("\nMy IP addresses:\n");
	for (unsigned int i=0; i < m_server->GetNumberOfAddresses(); i++){
		printf("%i. %s\n", i+1, m_server->GetLocalIP(i));
	}

	printf("\nMy GUID is %s\n", m_server->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString());
	puts("'quit' to quit. 'stat' to show stats. 'ping' to ping.\n'ban' to ban an IP from connecting.\n'kick to kick the first connected player.\nType to talk.");
}
void Server::Update(){
	RakSleep(30);
	if (kbhit()){
		Gets(message,sizeof(message));
		if (strcmp(message, "quit")==0){
			puts("Quitting.");
			return;
		}
		if (strcmp(message, "stat")==0){
			rss=m_server->GetStatistics(m_server->GetSystemAddressFromIndex(0));
			StatisticsToString(rss, message, 2);
			printf("%s", message);
			printf("Ping %i\n", m_server->GetAveragePing(m_server->GetSystemAddressFromIndex(0)));
		}
		if (strcmp(message, "ping")==0){
			m_server->Ping(clientID);
		}
		if (strcmp(message, "getconnectionlist")==0){
			RakNet::SystemAddress systems[10];
			unsigned short numConnections=10;
			m_server->GetConnectionList((RakNet::SystemAddress*) &systems, &numConnections);
			for (int i=0; i < numConnections; i++){
				printf("%i. %s\n", i+1, systems[i].ToString(true));
			}
		}
		char message2[2048];
		message2[0]=0;
		//strcpy(message2, "6 ");
		sprintf(message2, "6 %.0f %.0f %.0f %.0f %.0f %.0f", (float)m_maps[0], (float)m_maps[1], (float)m_maps[2], (float)m_maps[3], (float)m_maps[4], (float)m_maps[5]);
		strcat(message2, message);
		m_server->Send(message2, (const int) strlen(message2)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
	}
	//std::cout<<(IrrMngr::Inst()->getTime())<<std::endl;
	for (p=m_server->Receive(); p; m_server->DeallocatePacket(p), p=m_server->Receive()){
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
            m_server->Send(identificador, (const int) strlen(identificador)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
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
			m_server->Send(message, (const int) strlen(message)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, p->systemAddress, true);

			break;
		}
	}
}

unsigned char Server::GetPacketIdentifier(RakNet::Packet *p){
	if (p==0)
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP){
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	}
	else
		return (unsigned char) p->data[0];
}

std::vector<int> Server::listaMapas(){
    time_t timer;
    time(&timer);
    srand (timer);
    int x=0;
    std::vector<int> nums;
    std::vector<int> result;

    for(int i=0;i<6;i++) nums.push_back(i);
    while(nums.size()!=0){
        x = rand() % nums.size();
        result.push_back(nums[x]);
        nums.erase(nums.begin()+x);
    }
    std::cout<<result[0]<<" "<<result[1]<<" "<<result[2]<<" "<<result[3]<<" "<<result[4]<<" "<<result[5]<<" "<<std::endl;
    return result;

}
