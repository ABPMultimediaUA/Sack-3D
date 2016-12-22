#include "Bala.h"

Bala::Bala(ISceneManager* smgr, vector3df pos, IrrlichtDevice* device)
{
    //ctor
    tiempoVida = 1000;
    velocidad = 20;
    balaBodyDef.type = b2_kinematicBody;
    balaBodyDef.bullet = true;
    balaNode = smgr->addCubeSceneNode(8);
    balaNode->setPosition(pos);
    smgr->getMeshManipulator()->setVertexColors(balaNode->getMesh(), SColor(255, rand()%255, rand()%255, rand()%255));
    timerIrr = device->getTimer();
    timerbala = timerIrr->getTime();
}

Bala::~Bala()
{
    //dtor
}

Bala::getTime(void)
{
        return timerbala;
}

Bala::setTime(void)
{
        timerbala = timerIrr->getTime();
}
