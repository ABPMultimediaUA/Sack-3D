
#include "Platform.h"
#include "World.h"
#include "PhysicBody/PBDefault.h"
#include "PhysicBody/PBDefaultSensor.h"

Platform::Platform(bool mata, b2Vec2 pos, irr::core::vector3df tam,irr::video::SColor color){
    if(!mata){
            std::cout<<"plat "<<std::endl;
        m_id = m_gameObject.Inicialize(
            new PBDefault()
            ,M_SUELO
            ,M_PLAYER|M_SUELO|M_COGIBLE|M_BALA|M_TELEPORT|M_MUELLE|M_COGIBLESENSOR|M_PINCHO|M_SPAWNER
            ,0
            ,pos
            ,tam
            ,color
        );
    }
    else{
        std::cout<<"plat1 "<<std::endl;
        m_id = m_gameObject.Inicialize(
            new PBDefaultSensor()
            ,M_SUELO
            ,M_PLAYER|M_SUELO|M_COGIBLE|M_BALA|M_TELEPORT|M_MUELLE|M_COGIBLESENSOR|M_PINCHO|M_SPAWNER
            ,DATA_PINCHO
            ,pos
            ,tam
            ,color
        );
        m_gameObject.SetVisible(false);
    }
}
Platform::~Platform(){}
int Platform::GetId(){return m_id;}
