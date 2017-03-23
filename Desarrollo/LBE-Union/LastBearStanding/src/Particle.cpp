#include "Particle.h"
#include "World.h"


Particle::Particle(PhysicBody *physicBody, b2Vec2 pos, irr::core::vector3df tam, irr::video::SColor color, b2Vec2 vel, int tiempoVida)
:m_destruir(false),m_tiempoVida(tiempoVida){
    m_pIrrMngr = IrrMngr::Inst();
    m_id = m_gameObject.Inicialize(physicBody,pos,tam,color);
    m_timer2Kill = m_pIrrMngr->getTimer();
    m_time2Kill = m_timer2Kill->getTime();
    m_gameObject.SetLinearVelocity(vel);
}

Particle::~Particle(){}
void Particle::actualiza(){
    m_gameObject.Update();
    if(m_pIrrMngr->getTime()-m_time2Kill>m_tiempoVida){m_destruir = true;}
}
int Particle::GetId(){
    return m_id;
}

