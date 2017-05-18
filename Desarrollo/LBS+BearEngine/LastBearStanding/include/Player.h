#ifndef PLAYER_H
#define PLAYER_H

#include "Cogible.h"


#define LEVANTADO        1
#define MUERTO_DORMIDO   2
#define AGACHADO         3
#define PLAYER           10
#define PIESPLAYER       100

class MyEventReceiver;
class Client;
class Player: public Cogible{
    public:
        Player(b2Vec2 pos, char *texture,int mando);
        virtual ~Player();
        virtual void actualiza(MyEventReceiver *events = NULL);
        virtual void teletransportar();
        virtual void mover(MyEventReceiver *events);
        virtual void saltar();
        virtual void CogerTirar();
        virtual void morir();
        virtual void usar();
        virtual void BloodExplosion();
        virtual void fingirMuerte();
        virtual void recibeImpulso(float fuerza);
        virtual void Soltar();
        virtual b2Vec2 getPosition();
        virtual int getMando();
        virtual bool getSaltando();
        virtual bool getDobleSaltando();
        virtual bool getCogiendo();
        virtual bool getPuedoCoger();
        virtual bool getMuerto();
        virtual Cogible* getObjCogido();
        virtual Cogible* getObjPuedoCoger();
        virtual void setSaltando(bool aux);
        virtual void setDobleSaltando(bool aux);
        virtual void setCogiendo(bool aux);
        virtual void setPuedoCoger(bool aux);
        virtual void setObjCogido(Cogible* aux);
        virtual void setObjPuedoCoger(Cogible* aux);
        virtual void setNextPos(b2Vec2 pos);
        virtual void setParaMorir(bool aux);
        virtual int  getDireccion();
        virtual char* getIp();
        void setClientPort(char aux[]);
        void setServerPort(char aux[]);
        virtual int getEstado();
        virtual char* getId();
        virtual char* getServerPort();
        virtual char* getClientPort();
        virtual void  setIp(char aux[]);
        virtual void  setId(char aux[]);
    protected:
        int estado;
        int direccion;
        int lastDir;
        float x;
        float y;
        char ip[64];
        char serverPort[30];
        char clientPort[30];
        char id[30];
        float vel;
        int moviendoA;
        int moviendo;
        float salto ;
        bool boton_saltar;
        bool boton_coger;
        bool boton_muerto;
        bool boton_muerteBots;
        int mando;
        bool cogiendo;
        bool puedoCoger;
        bool dobleSaltando;
        bool fingiendoMuerte;
        bool saltando;
        bool paraMorir;
        bool muerto;
        b2Vec2 nextPos;
        Client *m_pClient;
        Cogible* objCogido;
        Cogible* objPuedoCoger;
		MyEventReceiver* eventReceiver;
		b2Vec2 velActual;
		uint32 time2Animation;
};

#endif
