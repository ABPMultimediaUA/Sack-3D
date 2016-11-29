#ifndef PLAYER_H
#define PLAYER_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>
#include <IrrManager.h>
#include <PhysicWorld.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Player
{
    public:
        Player();
        void update();
        void mover(b2Vec2 vel);
        virtual ~Player();

    protected:

    private:
		IMeshSceneNode* mesh;

	    b2Body* body;
        b2PolygonShape* polyShape;
        b2Fixture* personFixture;

        int x;
        int y;
};

#endif // PLAYER_H
