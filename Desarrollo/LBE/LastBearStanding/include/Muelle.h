
#ifndef MUELLE_H
#define MUELLE_H

#include "GameObject.h"
#include <irrlicht.h>

class Muelle:public GameObject{
    public:
        Muelle(float f , b2Vec2 pos, irr::core::vector3df tam = irr::core::vector3df(1.5f, 0.5f, 1.5f),irr::video::SColor color = irr::video::SColor(0, 255, 255, 255)); 	///< Constructor
        float getFuerza();
        ~Muelle();
    private:
	    float m_fuerza;
};
#endif
