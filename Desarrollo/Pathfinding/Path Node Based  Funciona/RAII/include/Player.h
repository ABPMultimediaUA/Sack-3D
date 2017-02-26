
#ifndef PLAYER_H
#define PLAYER_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>
#include "MyEventReceiver.h"
#include "Cogible.h"

class Player: public Cogible{
    public:
        Player(b2Vec2 pos, int mando);
        virtual ~Player(){}
        void InicializeFixtures(int mode);
        void DestroyFixtures();
        void actualiza();
        void mover();
        void muevo(int x, int y);
        void saltar();
        void CogerTirar();
        void fingirMuerte();
        void recibeImpulso(float fuerza);
        void teletransportar();
        void morir();
        void Soltar();
        void usar();
        irr::core::vector3df getPosition(){return irr::core::vector3df(body->GetPosition().x,body->GetPosition().y,0);}
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

    protected:
        irr::scene::IMeshSceneNode* node;
        b2Body* body;
        b2PolygonShape* polyShape;
        b2Fixture* personFixture;
        b2RevoluteJoint* joint;
        b2RevoluteJointDef* jointDef  = NULL;

        float nodox;
        float nodoy;
        bool moviendo = false;

        int x;
        int y;
        float vel = 7;
        float salto = 18.0f;
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
