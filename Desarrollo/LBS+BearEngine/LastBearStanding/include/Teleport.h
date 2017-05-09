
#ifndef TELEPORT_H
#define TELEPORT_H

#include "GameObject.h"


class Teleport{
    public:
        Teleport(int id, int p, b2Vec2 pos);
        virtual ~Teleport();
        int getTeleportId();
        int GetId();
        int getTeleportPartnerId();
        b2Vec2 getPosition();
    private:
        GameObject m_gameObject;
        int m_teleportId;
	    int m_id;
	    int m_partner;
};
#endif
