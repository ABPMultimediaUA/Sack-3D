
#ifndef MUELLE_H
#define MUELLE_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>

class Muelle{
    public:
        Muelle(float f , irr::core::vector3df pos, irr::core::vector3df tam = irr::core::vector3df(1.5f, 0.5f, 1.5f),irr::video::SColor color = irr::video::SColor(0, 255, 255, 255)); 	///< Constructor
        float getFuerza();
        b2Body* getBody();
        virtual ~Muelle();
    private:
        irr::scene::IMeshSceneNode* node; 
	    b2Body* body;
	    float fuerza;
};

#endif
