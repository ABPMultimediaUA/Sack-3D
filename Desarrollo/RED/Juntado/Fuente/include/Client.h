#ifndef CLIENT_H
#define CLIENT_H

#include "MessageIdentifiers.h"

#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include "RakNetTypes.h"
#include "BitStream.h"
#include "PacketLogger.h"
#include <assert.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include "RakNetTypes.h"
#ifdef _WIN32
#include "Kbhit.h"
#include "WindowsIncludes.h" // Sleep
#else
#include "Kbhit.h"
#include <unistd.h> // usleep
#endif
#include "Gets.h"

#if LIBCAT_SECURITY==1
#include "SecureHandshake.h" // Include header for secure handshake
#endif
#include "Player.h"
using namespace std;

class Client
{
    public:
        Client();
        RakNet::RakNetStatistics *rss;
        RakNet::RakPeerInterface *client;
        RakNet::Packet* p;
        //RakNet::SocketDescriptor socketDescriptor;
        unsigned char packetIdentifier;
        bool isServer;
        RakNet::SystemAddress clientID;
        void iniciar();
        unsigned char GetPacketIdentifier(RakNet::Packet *p);
        virtual ~Client();

    protected:

    private:
};

#endif // CLIENT_H
