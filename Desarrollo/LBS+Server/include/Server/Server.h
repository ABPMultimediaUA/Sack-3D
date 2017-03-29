#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include "IrrManager.h"
#include "RakPeerInterface.h"

class Server{
	public:
		Server();
		~Server();
		void Update();
	private:
		unsigned char GetPacketIdentifier(RakNet::Packet *p);
		std::vector<int> listaMapas();
		RakNet::RakPeerInterface *m_server;
		RakNet::SystemAddress clientID=RakNet::UNASSIGNED_SYSTEM_ADDRESS;
		unsigned char packetIdentifier;
		RakNet::RakNetStatistics *rss;
		std::vector<int> m_maps;
        irr::ITimer* timer2Start;
        irr::f32 time2Start;
		char message[2048];
		RakNet::Packet* p;
		int clID = 0;
		bool m_started;
};

#endif // SERVER_H
