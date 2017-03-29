
#ifndef TELEPORT_H
#define TELEPORT_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>

class Teleport{
    public:
        Teleport(int i, int p, irr::core::vector3df pos, irr::core::vector3df tam = irr::core::vector3df(0.5f, 3.f, 1.f) ,irr::video::SColor color = irr::video::SColor(0, 100, 100, 255)); 	///< Constructor
        b2Body* getBody();
        int getTeleportId();
        int getTeleportPartnerId();
        virtual ~Teleport(){}
    private:
        irr::scene::IMeshSceneNode* node; 
	    b2Body* body;
	    int id;
	    int partner;
};
#endif
