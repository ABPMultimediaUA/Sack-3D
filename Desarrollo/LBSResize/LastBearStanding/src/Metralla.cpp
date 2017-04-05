#include "PhysicBody/PBMetralla.h"
#include "Metralla.h"
#include "World.h"

Metralla::Metralla(b2Vec2 pos,b2Vec2 vel):m_destruir(false),m_tiempoVida(300){
    m_pIrrMngr = IrrMngr::Inst();
    int i = rand()%3;
    irr::video::SColor color;
    switch(i){
    	case 0:
    		color = irr::video::SColor(255,147, 123, 28);
    	break;
    	case 1:
    		color = irr::video::SColor(255,175, 119, 15);
    	break;
    	case 2:
    		color = irr::video::SColor(255,100,100,100);
    	break;
    }
    m_id = m_gameObject.Inicialize(new PBMetralla(),pos,irr::core::vector3df(0.03f,0.03f,0.03f),color);
    m_timer2Kill = m_pIrrMngr->getTimer();
    m_time2Kill = m_timer2Kill->getTime();
    m_gameObject.SetLinearVelocity(vel);
}

Metralla::~Metralla(){
}
void Metralla::actualiza(){
    m_gameObject.Update();
    if(m_pIrrMngr->getTime()-m_time2Kill>m_tiempoVida){m_destruir = true;}
}
void Metralla::SetLinearVelocity(b2Vec2 vel){
    m_gameObject.SetLinearVelocity(vel);
}
int Metralla::GetId(){
    return m_id;
}
