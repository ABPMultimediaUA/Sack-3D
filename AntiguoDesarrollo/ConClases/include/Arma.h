#ifndef ARMA_H
#define ARMA_H


#include <Box2D/Box2D.h>
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Arma
{
    public:
        Arma();
        void actualiza();
        b2Body* getBody();
        virtual ~Arma();

    protected:

    private:
        IMeshSceneNode* node;
	    b2Body* body;
};

#endif // ARMA_H
