#include "PhysicBody/PBMetralla.h"
#include "Metralla.h"
#include "World.h"
#include "SDL.h"

Metralla::Metralla(b2Vec2 pos,b2Vec2 vel):m_destruir(false),m_tiempoVida(300){
    m_pBearMngr = BearMngr::Inst();
    m_id = m_gameObject.Inicialize(new PBMetralla(),pos,glm::vec3(0.03f,0.03f,0.03f),"BearEngine/res/arma.obj");
    m_time2Kill = SDL_GetTicks();
    m_gameObject.SetLinearVelocity(vel);
}

Metralla::~Metralla(){
}
void Metralla::actualiza(){
    m_gameObject.Update();
    if(SDL_GetTicks()-m_time2Kill>m_tiempoVida){m_destruir = true;}
}
void Metralla::SetLinearVelocity(b2Vec2 vel){
    m_gameObject.SetLinearVelocity(vel);
}
int Metralla::GetId(){
    return m_id;
}
