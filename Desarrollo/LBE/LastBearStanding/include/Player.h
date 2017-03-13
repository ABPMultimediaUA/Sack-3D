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
        Player(b2Vec2 pos, int mando, irr::video::SColor color);
        virtual ~Player();
        void InicializeFixtures(int mode);
        void DestroyFixtures();
        virtual void actualiza();
        void teletransportar();
        virtual void mover();
        virtual void saltar();
        virtual void CogerTirar();
        void fingirMuerte();
        void recibeImpulso(float fuerza);
        virtual void morir();
        void Soltar();
        void usar();
        b2Vec2 getPosition();
        int getMando();
        bool getSaltando();
        bool getDobleSaltando();
        bool getCogiendo();
        bool getPuedoCoger();
        bool getMuerto();
        Cogible* getObjCogido();
        Cogible* getObjPuedoCoger();
        void setSaltando(bool aux);
        void setDobleSaltando(bool aux);
        void setCogiendo(bool aux);
        void setPuedoCoger(bool aux);
        void setObjCogido(Cogible* aux);
        void setObjPuedoCoger(Cogible* aux);
        void setNextPos(b2Vec2 pos);
        void setParaMorir(bool aux);
        int  getDireccion();
        char* getIp();
        void setClientPort(char aux[]);
        void setServerPort(char aux[]);
        int getEstado();
         char* getId();
        char* getServerPort();
        char* getClientPort();
        void  setIp(char aux[]);
        virtual void  setId(char aux[]);


    protected:
        b2PolygonShape* polyShape;
        b2Fixture* personFixture;
        b2RevoluteJoint* joint;
        b2RevoluteJointDef* jointDef;
        int estado;
        int direccion;
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
};

#endif
