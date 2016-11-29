#ifndef BALA_H
#define BALA_H

#include <iostream>
#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <vector>

#define SCREENWIDTH 1366
#define SCREENHEIGHT 768

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Bala
{
    public:
        virtual ~Bala();
        //Atrubutos de la clase
        int tiempoVida;
        int velocidad;
        b2BodyDef balaBodyDef;
        b2Body* balaBody;
        b2Fixture* balaFixure;
        b2FixtureDef balaFixureDef;
        IMeshSceneNode* balaNode;
        f32 timerbala;
        ITimer* timerIrr;

        //Metodos de la clase
        Bala(ISceneManager*, vector3df, IrrlichtDevice*);  // This is the constructor
        getTime();
        setTime();

    protected:

    private:
};

#endif // BALA_H
