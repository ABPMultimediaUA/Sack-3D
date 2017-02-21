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
#include "PlayerRed.h"
using namespace std;

class Client
{
    public:
        Client();
        RakNet::RakNetStatistics *rss;
        RakNet::RakPeerInterface *client;
        RakNet::Packet* p;
        //RakNet::SocketDescriptor socketDescriptor;
        struct TPlayersRed{
            //PlayerRed* player;
            char id[30];
        };
        unsigned char packetIdentifier;
        bool isServer;
        RakNet::SystemAddress clientID;
        void iniciar();
        void recibir();
        void enviar();
        void enviarSalto(int i);
        void enviarCogido(int cogible);
        void enviarMoviendo(int moviendo);
        void dispararPistola(long int x, long int y, int direc);
        void dispararEscopeta(long int x, long int y, int direc);
        void enviarDisparo(int arma);
        PlayerRed* crearPlayer(char* i);
        char* getIdCliente(){return idCliente;}
        int getNumPlayersRed(){return numPlayersRed;}
        TPlayersRed playersRed [3];
        unsigned char GetPacketIdentifier(RakNet::Packet *p);
        virtual ~Client();

    protected:

    private:
        char idCliente[30];
        int numPlayersRed;
};

#endif // CLIENT_H
