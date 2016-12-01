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
        Player(vector3df pos);
        void update();
        void mover(int);
        void saltar();
        b2Body* getBody();
        virtual ~Player();

        bool cogiendo;
        bool puedoCoger;

    protected:
        IMeshSceneNode* mesh;

        b2Body* body;
        b2PolygonShape* polyShape;
        b2Fixture* personFixture;

        int x;
        int y;
        int vel;
    private:
		
};

#endif // PLAYER_H
