#include "PhysicBody/PBSpawner.h"
#include "IrrManager.h"
#include "Escopeta.h"
#include "Pistola.h"
#include "Granada.h"
#include "Spawner.h"
#include "World.h"

Spawner::Spawner(int tipo, int modelo , b2Vec2 pos )
:tipo(tipo),modelo(modelo){
    m_pWorld = World::Inst();
    m_pIrrMngr = IrrMngr::Inst();
    cogiendo = true;
    cadencia = 2000;
    timer = m_pIrrMngr->getTimer();
    time = timer->getTime();
    m_id = m_gameObject.Inicialize(
        new PBSpawner()
        ,pos
        ,irr::core::vector3df(1.f,.2f,1.f)
        ,irr::video::SColor(255, 255, 255, 255)
    );
    generar();
}
Spawner::~Spawner(){}

void Spawner::actualiza(){
    if(!cogiendo && m_pIrrMngr->getTime()-time>cadencia){
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
    time = timer->getTime();
    cogiendo = false;
}
void Spawner::generar(){
    switch(tipo){
        case 1: objCogido = m_pWorld->AddCogible(new Pistola(this,modelo,b2Vec2(m_gameObject.GetPosition().x,m_gameObject.GetPosition().y)));  break;
        case 2: objCogido = m_pWorld->AddCogible(new Escopeta(this,modelo,b2Vec2(m_gameObject.GetPosition().x,m_gameObject.GetPosition().y))); break;
        case 3: objCogido = m_pWorld->AddCogible(new Granada(this,modelo,b2Vec2(m_gameObject.GetPosition().x,m_gameObject.GetPosition().y)));  break;
    }
    cogiendo = true;
    coger(objCogido);
}
int Spawner::GetId(){return m_id;}
