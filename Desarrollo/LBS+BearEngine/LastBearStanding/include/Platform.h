
#ifndef PLATFORM_H
#define PLATFORM_H

#include "GameObject.h"
#include <irrlicht.h>

class Platform{
    public:
        Platform(bool mata, b2Vec2 pos, glm::vec3 tam,irr::video::SColor color);
        ~Platform();
        int GetId();
    private:
        GameObject m_gameObject;
        int m_id;
};

#endif
