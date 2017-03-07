#include "IrrManager.h"
#include "Escopeta.h"
#include "Pistola.h"
#include "Granada.h"
#include "Spawner.h"
#include "World.h"

Spawner::Spawner(int tipo, int modelo , b2Vec2 pos )
:GameObject(pos,irr::core::vector3df(1.f,.2f,1.f),irr::video::SColor(255, 255, 255, 255)),tipo(tipo),modelo(modelo){
    cogiendo = true;
    cadencia = 2000;
    timer = m_pIrrMngr->getTimer();
    time = timer->getTime();
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x+(m_tam.X/2),-1*(pos.y-(m_tam.Y/2)));
    bodyDef.type = b2_staticBody;
    m_pBody  = m_pWorld->GetWorld()->CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox((m_tam.X/2),(m_tam.Y/2));
    fixtureDef.shape = &polyShape;
    fixtureDef.isSensor = true;
    b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
    b2Filter filter = fixture->GetFilterData();
    filter.categoryBits = 16;
    fixture->SetFilterData(filter);
    generar();
}
Spawner::~Spawner(){}

void Spawner::actualiza(){
    if(!cogiendo && m_pIrrMngr->getTime()-time>cadencia){
        generar();
    }
}
void Spawner::coger(Cogible* obj){
    objCogido = obj;
    b2Vec2 aux;
    b2Vec2 aux2;
    b2RevoluteJointDef jointDef;
    objCogido->setExpuesto(true);
    jointDef.enableLimit = true;
    jointDef.lowerAngle = 0;
    jointDef.bodyA = m_pBody;
    jointDef.bodyB = objCogido->getBody();
    jointDef.localAnchorA.Set(0,0.3f);
    jointDef.localAnchorB.Set(0,0);
    joint = (b2RevoluteJoint*)m_pWorld->GetWorld()->CreateJoint(&jointDef);
    cogiendo = true;
}
void Spawner::soltar(){
    m_pWorld->GetWorld()->DestroyJoint(joint);
    time = timer->getTime();
    cogiendo = false;
}
void Spawner::generar(){
    switch(tipo){
        case 1: objCogido = m_pWorld->AddCogible(new Pistola(this,modelo,b2Vec2(m_pos.x,m_pos.y)));  break;
        case 2: objCogido = m_pWorld->AddCogible(new Escopeta(this,modelo,b2Vec2(m_pos.x,m_pos.y))); break;
        case 3: objCogido = m_pWorld->AddCogible(new Granada(this,modelo,b2Vec2(m_pos.x,m_pos.y)));  break;
    }
    cogiendo = true;
    coger(objCogido);
}
