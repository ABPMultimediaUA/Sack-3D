#include "Particle.h"
#include "World.h"
#include "SDL.h"


Particle::Particle(PhysicBody *physicBody, b2Vec2 pos, glm::vec3 tam, int tiempoVida,  char *model, char *texture)
:m_destruir(false),m_tiempoVida(tiempoVida){
    m_pBearMngr = BearMngr::Inst();
    m_id = m_gameObject.Inicialize(physicBody,pos,tam,model,texture);
    m_time2Kill = SDL_GetTicks();
}

Particle::~Particle(){}
void Particle::SetGravity(float gravity){
	m_gameObject.SetGravity(gravity);
}
void Particle::actualiza(){
    m_gameObject.Update();
    if(SDL_GetTicks()-m_time2Kill>m_tiempoVida){m_destruir = true;}
}
void Particle::SetAngularVelocity(float imp){
    m_gameObject.SetAngularVelocity(imp);
}
void Particle::SetLinearVelocity(b2Vec2 vel){
    m_gameObject.SetLinearVelocity(vel);
}
int Particle::GetId(){
    return m_id;
}

