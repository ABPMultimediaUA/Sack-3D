#ifndef PLAYER_H
#define PLAYER_H


#include <Box2D/Box2D.h>
#include <irrlicht.h>
#include "MyEventReceiver.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Player
{
    public:
        Player(vector3df pos);
        void update();
        void mover();
        void saltar();
        vector3df getPosition();
        bool getSaltando();
        void setSaltando(bool aux);
        void setDobleSaltando(bool);
        bool getDobleSaltando();
        bool getCogiendo();
        void setCogiendo(bool aux);
        void fingirMuerte();
        int getDireccion();
        bool getPuedoCoger();
        void setPuedoCoger(bool aux);
        void crearJoint(b2Body*, b2Body*);
        void romperJoint();
        b2Body* getBody();
        virtual ~Player();

    protected:
        IMeshSceneNode* node;
        b2Body* body;
        b2PolygonShape* polyShape;
        b2Fixture* personFixture;
        b2RevoluteJoint* joint;
        b2RevoluteJointDef* jointDef;
        int x;
        int y;
        int vel;
        int salto;
        bool cogiendo;
        int direccion;
        bool puedoCoger;
        bool dobleSaltando;
        bool fingiendoMuerte;
        bool saltando;
        vector3df tam;
		MyEventReceiver* eventReceiver;
    private:
};

#endif // PLAYER_H
