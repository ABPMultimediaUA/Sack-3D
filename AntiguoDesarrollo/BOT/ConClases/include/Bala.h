#ifndef BALA_H
#define BALA_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Bala
{
    public:
        Bala();
        void actualiza();
        b2Body* getBody();
        IMeshSceneNode* getNode();
        b2Fixture* getbalaFixture();
        int getTime();
        int getTimeVida();
        virtual ~Bala();

        int tiempoVida;
        int velocidad;
        f32 timerbala;
        ITimer* timerIrr;

    protected:
        IMeshSceneNode* node;
	    b2Body* body;
	     b2Fixture* balaFixture;

    private:
};

#endif // BALA_H
