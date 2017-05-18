#ifndef CLIENT_H
#define CLIENT_H

#include "MessageIdentifiers.h"
#include <string>
#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include "RakNetTypes.h"
#include "BitStream.h"
#include "PacketLogger.h"
#include <assert.h>
#include <iostream>
#include <vector>
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
        struct TParams{
            char var[30];
        };
        int idPlayerInt;
        unsigned char packetIdentifier;
        bool isServer;
        bool getRun(){return run;}
        bool comprobacion(char* aux);
        RakNet::SystemAddress clientID;
        void iniciar(std::string gameMode, std::string IP, int difficult);
        void PacketFunction(int aux);
        void recibir();
        void enviar(int aux = -1);
        void enviarSalto(int i, int aux = -1);
        void enviarCogido(int cogible, int aux = -1);
        void enviarMoviendo(int moviendo, int aux = -1);
        void enviarUsar(int aux = -1);
        void enviarMuerto(int aux = -1);
        void enviarHacerseMuerto(int aux = -1);
        void analizarPaquete0();
        void analizarPaquete1();
        void analizarPaquete2();
        void analizarPaquete3();
        void analizarPaquete4();
        void analizarPaquete5();
        void analizarPaquete6();
        void analizarPaquete7();
        void analizarPaquete8();
        void setMaps(std::vector<int> mapas);
        void singleMaps();
        std::vector<int> getMaps(){return maps;}
        bool comprobarPaquete(RakNet::Packet* p);
        char* getIdCliente(){return idCliente;}
        int getNumPlayersRed(){return numPlayersRed;}
        unsigned char GetPacketIdentifier(RakNet::Packet *p);
        TPlayersRed playersRed [3];
        TParams params [11];
        int getDifficult(){ return dificultad;}

    protected:

    private:
        int dificultad;
        std::vector<int> maps;
        std::string gameMode;
        std::string IP;
        static Client* pinstance;
        char idCliente[30];
        int numPlayersRed;
        bool run;
        int iterador;
        const Type2Func packetFunction[10] = {
              { 0         , analizarPaquete0    }
            , { 1         , analizarPaquete1    }
            , { 2         , analizarPaquete2    }
            , { 3         , analizarPaquete3    }
            , { 4         , analizarPaquete4    }
            , { 5         , analizarPaquete5    }
            , { 6         , analizarPaquete6    }
            , { 7         , analizarPaquete7    }
            , { 8         , analizarPaquete8    }
            , { -1        , 0                   }
        };

};

#endif // CLIENT_H
