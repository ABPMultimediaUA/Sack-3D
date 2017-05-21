#include "PhysicBody/PBSpawner.h"
#include "PhysicBody/PBCotton.h"
#include "BearManager.h"
#include "Particle.h"
#include "Escopeta.h"
#include "Pistola.h"
#include "Granada.h"
#include "Spawner.h"
#include "World.h"
#include "SDL.h"

Spawner::Spawner(int tipo, int modelo , b2Vec2 pos, int idc )
:tipo(tipo),modelo(modelo),m_pos(pos){
    m_pWorld = World::Inst();
    m_pBearMngr = BearMngr::Inst();
    cogiendo = true;
    cadencia = 2000;
    time = SDL_GetTicks();
    id=idc;
    cont=0;
    m_id = m_gameObject.Inicialize(
        new PBSpawner()
        ,pos
        ,glm::vec3(0.05f,.035f,0.01f)
        ,"BearEngine/res/spawner.obj"
        ,"media/Images/otro.png"
    );
    generar();
}
Spawner::~Spawner(){}

void Spawner::actualiza(){
    if(!cogiendo && SDL_GetTicks()-time>cadencia){
        generar();
    }
}
void Spawner::coger(Cogible *obj){
    objCogido->setExpuesto(true);
    m_gameObject.Catch(objCogido->GetId());
    objCogido = obj;
    cogiendo = true;
}
void Spawner::soltar(){
    m_gameObject.Release();
    time = SDL_GetTicks();
    cogiendo = false;
}
void Spawner::generar(){
    ParticleSpawn();
    int f = tipo*1000+id*100+cont;
    cont++;
    switch(tipo){
        case 1: objCogido = m_pWorld->AddCogible(new Pistola(this,modelo,b2Vec2(m_gameObject.GetPosition().x,m_gameObject.GetPosition().y), f));  break;
        case 2: objCogido = m_pWorld->AddCogible(new Escopeta(this,modelo,b2Vec2(m_gameObject.GetPosition().x,m_gameObject.GetPosition().y), f)); break;
        case 3: objCogido = m_pWorld->AddCogible(new Granada(this,modelo,b2Vec2(m_gameObject.GetPosition().x,m_gameObject.GetPosition().y), f));  break;
    }
    cogiendo = true;
    coger(objCogido);
}

void Spawner::ParticleSpawn(){
    b2Vec2 pos = m_gameObject.GetPosition();
    pos.y *= -1;
    pos.x=pos.x/2.0f;
    pos.y=pos.y/2.0f;
    for (int i = 0; i < 20; ++i){
        glm::vec3 tam;
        tam.x = (rand()%10)/500.f;
        tam.y = tam.x;
        tam.z = 0.02f;
        Particle *cap = m_pWorld->AddParticle(new Particle(new PBCotton(),pos,tam, rand()%300+300));
        cap->SetGravity(0.05f);
        b2Vec2 capVel;
        capVel.x = (rand()%10-5)/10.f;
        capVel.y = (rand()%10)/10.f;
        cap->SetLinearVelocity(capVel);
    }
}
int Spawner::GetId(){return m_id;}
b2Vec2 Spawner::GetPosition(){
    return m_pos;
}
