#ifndef PLAYER_H
#define PLAYER_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>

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
        void mover(int);
        void saltar();
        b2Body* getBody();
        virtual ~Player();

        bool cogiendo;
        bool puedoCoger;

    protected:

    private:
		IMeshSceneNode* mesh;

	    b2Body* body;
        b2PolygonShape* polyShape;
        b2Fixture* personFixture;

        int x;
        int y;
        int vel;
};

#endif // PLAYER_H
