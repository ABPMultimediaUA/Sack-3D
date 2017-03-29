#include "PhysicBody/PBBullet.h"
#include "Metralla.h"
#include "World.h"

Metralla::Metralla(b2Vec2 pos,b2Vec2 vel):m_destruir(false),m_tiempoVida(1000){
    m_pIrrMngr = IrrMngr::Inst();
    m_id = m_gameObject.Inicialize(
	    		new PBBullet()
		    	,pos
		    	,irr::core::vector3df(0.1f,0.1f,0.1f)
		    	,irr::video::SColor(255,255,255,255)
	    	);
    m_timer2Kill = m_pIrrMngr->getTimer();
    m_time2Kill = m_timer2Kill->getTime();
    m_gameObject.SetLinearVelocity(vel);
}

Metralla::~Metralla(){}
void Metralla::actualiza(){
    m_gameObject.Update();
    if(m_pIrrMngr->getTime()-m_time2Kill>m_tiempoVida){m_destruir = true;}
}
int Metralla::GetId(){
    return m_id;
}
