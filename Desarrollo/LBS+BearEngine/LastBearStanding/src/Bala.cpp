#include "Bala.h"
#include "World.h"
#include "PhysicBody/PBBullet.h"
#include "SDL.h"

Bala::Bala( b2Vec2 pos,  int tiempoVidaP, int velocidad, float deviacionP, int dir,int tipo,  char *model, char *texture):
dir(dir),tiempoVida(tiempoVidaP),desviacion(deviacionP),destruir(false){
    m_pBearMngr = BearMngr::Inst();
    glm::vec3 tam;
    switch(tipo){
        case 1:tam = glm::vec3(0.02f,0.02f,0.02f);break;
        case 2:tam = glm::vec3(0.02f,0.02f,0.02f);break;
        case 3:tam = glm::vec3(0.02f,0.02f,0.02f);break;
    }
    pos.x = pos.x + (dir/5.0f);
    pos.x = pos.x/2.0f;
    pos.y = pos.y/2.0f;
    m_id = m_gameObject.Inicialize(new PBBullet(),pos,tam,model,texture);
    time2Kill = SDL_GetTicks();
    if(dir>0)m_vel.x = velocidad;
    else     m_vel.x = -velocidad;
    m_vel.y=0.0f;
    if(desviacion != 0 )m_vel.y = (((rand()% 10000) / 10000.0)*desviacion)-(desviacion/2);
    m_gameObject.SetLinearVelocity(m_vel);
    teletransportado = false;
}
Bala::~Bala(){}
void Bala::actualiza(){
    if(teletransportado) teletransportar();
    m_gameObject.Update();
    if(SDL_GetTicks()-time2Kill>tiempoVida){destruir = true;}
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
