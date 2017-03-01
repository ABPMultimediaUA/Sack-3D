
#ifndef PLATFORM_H
#define PLATFORM_H

#include <irrlicht.h>
#include <Box2D/Box2D.h>

class Platform{
    public:
        Platform(bool mata, irr::core::vector3df pos, irr::core::vector3df tam,irr::video::SColor color);
        virtual ~Platform();
    private:
        irr::scene::IMeshSceneNode* node = NULL;
	    b2Body* body;
};

#endif
