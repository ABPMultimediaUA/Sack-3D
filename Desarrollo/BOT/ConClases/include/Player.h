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
        b2Body* getBody();
        virtual ~Player();

        bool cogiendo;
        bool puedoCoger;

    protected:
        IMeshSceneNode* node;

        b2Body* body;
        b2PolygonShape* polyShape;
        b2Fixture* personFixture;

        int x;
        int y;
        int vel;
        int salto;
        vector3df tam;
    private:
		MyEventReceiver* eventReceiver;
};

#endif // PLAYER_H
