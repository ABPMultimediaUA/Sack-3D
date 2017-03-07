
#ifndef TELEPORT_H
#define TELEPORT_H

#include <irrlicht.h>
#include "GameObject.h"


class Teleport:public GameObject{
    public:
        Teleport(int id, int p, b2Vec2 pos); 	///< Constructor
        int getTeleportId();
        int getTeleportPartnerId();
        virtual ~Teleport();
    private:
	    int m_id;
	    int m_partner;
};
#endif
