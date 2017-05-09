#include "PhysicBody/PBDefault.h"
#include "Teleport.h"
#include "World.h"

Teleport::Teleport(int tpId, int partner, b2Vec2 pos)
:m_teleportId(tpId),m_partner(partner){
    m_id = m_gameObject.Inicialize(
        new PBDefault()
        ,M_TELEPORT
        ,M_BALA|M_COGIBLE|M_PLAYER
        ,DATA_TELEPORT
        ,pos
        ,glm::vec3(0.05f, 0.3f, 0.1f)
    );
    m_id = m_gameObject.GetId();
}
Teleport::~Teleport(){}
b2Vec2 Teleport::getPosition(){
	return m_gameObject.GetPosition();
}
int Teleport::getTeleportId(){return m_teleportId;}
int Teleport::GetId(){return m_id;}
int Teleport::getTeleportPartnerId(){return m_partner;}

