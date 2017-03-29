#ifndef PLATFORM_H
#define PLATFORM_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Platform
{
    public:
        Platform(vector3df pos, vector3df tam,SColor color);
        virtual ~Platform();

    protected:

    private:
    	IMesh* mesh;
	    b2Body* body;
};

#endif // PLATFORM_H
