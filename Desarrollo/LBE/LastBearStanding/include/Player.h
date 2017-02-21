
#ifndef PLAYER_H
#define PLAYER_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>
#include "MyEventReceiver.h"
#include "Cogible.h"

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
        char* getIp();
        char* getServerPort();
        char* getClientPort();
        char* getId();
        void setIp(char aux[]);
        void setServerPort(char aux[]);
        void setClientPort(char aux[]);
        void setId(char aux[]);
        int getEstado(){return estado;}
        int getDireccion();

    protected:
        irr::scene::IMeshSceneNode* node;
        b2Body* body;
        b2PolygonShape* polyShape;
        b2Fixture* personFixture;
        b2RevoluteJoint* joint;
        b2RevoluteJointDef* jointDef  = NULL;
        int estado;
        int direccion;
        int x;
        int y;
        char ip[64];
        char serverPort[30];
        char clientPort[30];
        char id[30];
        float vel = 7;
        float salto = 15.0f;
        int mando;
        bool cogiendo = false;
        bool puedoCoger = false;
        bool dobleSaltando = false;
        bool fingiendoMuerte = false;
        bool saltando = false;
        bool paraMorir = false;
        bool muerto = false;
        b2Vec2 nextPos;
		bool teletransportado = false;
        Cogible* objCogido;
        Cogible* objPuedoCoger;
        irr::core::vector3df tam;
		MyEventReceiver* eventReceiver;
		b2Vec2 velActual;
    private:
};

#endif
