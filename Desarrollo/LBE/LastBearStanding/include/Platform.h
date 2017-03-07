
#ifndef PLATFORM_H
#define PLATFORM_H

#include "GameObject.h"
#include <irrlicht.h>

class Platform:public GameObject{
    public:
        Platform(bool mata, b2Vec2 pos, irr::core::vector3df tam,irr::video::SColor color);
        ~Platform();
};

#endif
