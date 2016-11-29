#ifndef CUBOMIERDA_H
#define CUBOMIERDA_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class cuboMierda{
    public:
        cuboMierda(int x, int y);
        void actualiza();
        virtual ~cuboMierda();

    protected:

    private:
		IMeshSceneNode* node;
	    b2Body* body;
        int x;
        int y;
};

#endif // CUBOMIERDA_H
