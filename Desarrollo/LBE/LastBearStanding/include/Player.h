#ifndef PLAYER_H
#define PLAYER_H

#include "Cogible.h"


#define LEVANTADO        1
#define MUERTO_DORMIDO   2
#define AGACHADO         3
#define PLAYER           10
#define PIESPLAYER       100

class MyEventReceiver;

class Player: public Cogible{
    public:
        Player(b2Vec2 pos, int mando);
        virtual ~Player();
        void InicializeFixtures(int mode);
        void DestroyFixtures();
        void actualiza();
        void mover();
        void saltar();
        void CogerTirar();
        void fingirMuerte();
        void recibeImpulso(float fuerza);
        void teletransportar();
        void morir();
        void Soltar();
        void usar();
        b2Vec2 getPosition(){return body->GetPosition();}
        int getMando(){return mando;}
        bool getSaltando(){return saltando;}
        bool getDobleSaltando(){return dobleSaltando;}
        bool getCogiendo(){return cogiendo;}
        bool getPuedoCoger(){return puedoCoger;}
        bool getMuerto(){return muerto;}
        b2Body* getBody(){return body;}
        Cogible* getObjCogido(){return objCogido;}
        Cogible* getObjPuedoCoger(){return objPuedoCoger;}
        void setSaltando(bool aux){saltando = aux;}
        void setDobleSaltando(bool aux){dobleSaltando = aux;}
        void setCogiendo(bool aux){cogiendo = aux;}
        void setPuedoCoger(bool aux){puedoCoger = aux;}
        void setObjCogido(Cogible* aux){objCogido = aux;}
        void setObjPuedoCoger(Cogible* aux){objPuedoCoger = aux;}
        void setNextPos(b2Vec2 pos){teletransportado=true; nextPos = pos;}
        void setParaMorir(bool aux){paraMorir = aux;}
        int  getDireccion(){return direccion;}
        char* getIp(){return ip;}
        void setClientPort(char aux[]){strncpy(clientPort, aux, sizeof(clientPort));}
        void setServerPort(char aux[]){strncpy(serverPort, aux, sizeof(serverPort));}
        int getEstado(){return estado;}
        char* getId(){return id;}
        char* getServerPort(){return serverPort;}
        char* getClientPort(){return clientPort;}
        void  setIp(char aux[]){strncpy(ip, aux, sizeof(ip));}
        void  setId(char aux[]){strncpy(id, aux, sizeof(id));}


    protected:
        irr::scene::IMeshSceneNode* node;
        b2Body* body;
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
		bool teletransportado;
        Cogible* objCogido;
        Cogible* objPuedoCoger;
        irr::core::vector3df tam;
		MyEventReceiver* eventReceiver;
		b2Vec2 velActual;
};

#endif
