#ifndef BOT_H
#define BOT_H

#include <Player.h>
#include <Box2D/Box2D.h>
#include <irrlicht.h>
#include "IrrManager.h"
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class Bot : public Player
{
    public:
        Bot(vector3df pos);
        void update();
        int getMemership(float d);
        int getMayorValor(int x1, int x2, int x3);
        void huir(int dir);
        void quieto();
        virtual ~Bot();

    protected:

    private:
    	float distancia;
    	float membership;
    	int cerca;
    	int intermedio;
    	int lejos;
        IMeshSceneNode* mesh;
};

#endif // BOT_H
