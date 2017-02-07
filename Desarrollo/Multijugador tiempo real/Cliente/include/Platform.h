
#ifndef PLATFORM_H
#define PLATFORM_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>

class Platform{
    public:
        Platform(irr::core::vector3df pos, irr::core::vector3df tam,irr::video::SColor color);
        virtual ~Platform();
    private:
        irr::scene::IMesh* mesh;
	    b2Body* body;
};

#endif
