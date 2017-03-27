#include "Bala.h"
#include "World.h"
#include "PhysicBody/PBBullet.h"

Bala::Bala( b2Vec2 pos,  int tiempoVidaP, int velocidad, float deviacionP, int dir,int tipo):
dir(dir),tiempoVida(tiempoVidaP),desviacion(deviacionP),destruir(false){
    m_pIrrMngr = IrrMngr::Inst();
    irr::core::vector3df tam;
    switch(tipo){
        case 1:tam = irr::core::vector3df(0.1f,0.1f,0.1f);break;
        case 2:tam = irr::core::vector3df(0.1f,0.1f,0.1f);break;
        case 3:tam = irr::core::vector3df(0.1f,0.1f,0.1f);break;
    }
    pos.x = pos.x + dir;
    std::cout<<"bala "<<std::endl;
    m_id = m_gameObject.Inicialize(new PBBullet(),pos,tam,irr::video::SColor(255,255,255,255));
    timer2Kill = m_pIrrMngr->getTimer();
    time2Kill = timer2Kill->getTime();
    if(dir>0)m_vel.x = velocidad;
    else     m_vel.x = -velocidad;
    if(desviacion != 0 )m_vel.y = (((rand()% 10000) / 10000.0)*desviacion)-(desviacion/2);
    m_gameObject.SetLinearVelocity(m_vel);
    teletransportado = false;
}
Bala::~Bala(){}
void Bala::actualiza(){
    if(teletransportado) teletransportar();
    m_gameObject.Update();
    if(m_pIrrMngr->getTime()-time2Kill>tiempoVida){destruir = true;}
}
void Bala::teletransportar(){
    teletransportado = false;
    nextPos.x += dir;
    m_gameObject.SetPosition(b2Vec2(nextPos.x,nextPos.y));
    m_gameObject.SetLinearVelocity(m_vel);
}
int Bala::GetId(){
    return m_id;
}
