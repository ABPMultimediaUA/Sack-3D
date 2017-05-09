#include "Muelle.h"
#include "World.h"
#include "BearManager.h"
#include "PhysicBody/PBDefault.h"

Muelle::Muelle(float f, b2Vec2 pos, glm::vec3 tam){
    m_fuerza = f;
    m_id = m_gameObject.Inicialize(
        new PBDefault()
        ,M_MUELLE
        ,M_COGIBLE|M_PLAYER
        ,DATA_MUELLE
        ,pos
        ,tam
    );
}
Muelle::~Muelle(){}
float Muelle::getFuerza(){return m_fuerza;}
int Muelle::GetId(){return m_id;}
