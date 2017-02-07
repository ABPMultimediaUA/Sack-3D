
#ifndef MUELLE_H
#define MUELLE_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>

class Muelle{
    public:
        Muelle(float f , irr::core::vector3df pos, irr::core::vector3df tam = irr::core::vector3df(3, 1, 3),irr::video::SColor color = irr::video::SColor(255, 0, 255, 0)); 	///< Constructor
        float getFuerza();
        b2Body* getBody();
        virtual ~Muelle();
    private:
    	irr::scene::IMesh* mesh;
	    b2Body* body;
	    float fuerza;
};

#endif
