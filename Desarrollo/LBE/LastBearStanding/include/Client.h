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
class Client;

struct Type2Func {
     int A;
     void (Client::*p)();
};
class Client{
    public:
        static Client* Inst();
        Client();
        virtual ~Client();
        RakNet::RakNetStatistics *rss;
        RakNet::RakPeerInterface *client;
        RakNet::Packet* p;
        struct TPlayersRed{
            char id[30];
        };
        int idPlayerInt;
        unsigned char packetIdentifier;
        bool isServer;
        bool getRun(){return run;}
        bool comprobacion(char* aux);
        RakNet::SystemAddress clientID;
        void iniciar();
        void PacketFunction(int aux,char* param1,char* param2,char* param3,char* param4,char* param5,char* param6);
        void recibir();
        void enviar();
        void enviarSalto(int i);
        void enviarCogido(int cogible);
        void enviarMoviendo(int moviendo);
        void enviarUsar();
        void enviarMuerto();
        void analizarPaquete0();
        void analizarPaquete1();
        void analizarPaquete2();
        void analizarPaquete3();
        void analizarPaquete4();
        void analizarPaquete5();
        void analizarPaquete6(){run=true;}
        void analizarPaquete7();
        char* getIdCliente(){return idCliente;}
        int getNumPlayersRed(){return numPlayersRed;}
        unsigned char GetPacketIdentifier(RakNet::Packet *p);
        TPlayersRed playersRed [3];

    protected:

    private:
        static Client* pinstance;
        char idCliente[30];
        int numPlayersRed;
        irr::f32 timer;
        bool run;
        int iterador;
        char    *param1,
                *param2,
                *param3,
                *param4,
                *param5,
                *param6;
        const Type2Func packetFunction[9] = {
              { 0         , analizarPaquete0    }
            , { 1         , analizarPaquete1    }
            , { 2         , analizarPaquete2    }
            , { 3         , analizarPaquete3    }
            , { 4         , analizarPaquete4    }
            , { 5         , analizarPaquete5    }
            , { 6         , analizarPaquete6    }
            , { 7         , analizarPaquete7    }
            , { -1        , 0                   }
        };

};

#endif // CLIENT_H
