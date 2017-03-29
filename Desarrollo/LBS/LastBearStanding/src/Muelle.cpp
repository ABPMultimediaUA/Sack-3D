#include "Muelle.h"
#include "World.h"
#include "IrrManager.h"
#include "PhysicBody/PBDefault.h"

Muelle::Muelle(float f, b2Vec2 pos, irr::core::vector3df tam,irr::video::SColor color){
    m_fuerza = f;
    std::cout<<"mueelle "<<std::endl;
    m_id = m_gameObject.Inicialize(
        new PBDefault()
        ,M_MUELLE
        ,M_COGIBLE|M_PLAYER
        ,DATA_MUELLE
        ,pos
        ,tam
        ,color
    );
}
Muelle::~Muelle(){}
float Muelle::getFuerza(){return m_fuerza;}
int Muelle::GetId(){return m_id;}
