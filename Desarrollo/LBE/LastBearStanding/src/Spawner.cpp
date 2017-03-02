#include "IrrManager.h"
#include "Escopeta.h"
#include "Pistola.h"
#include "Granada.h"
#include "Spawner.h"
#include "World.h"

Spawner::Spawner(int tipo, int modelo , b2Vec2 pos ):pos(pos),tipo(tipo),modelo(modelo){
    cogiendo = true;
    cadencia = 2000;
    irr::core::vector3df tam(1.f,.2f,1.f);
    pos.x += (tam.X/2);
    pos.y  = -1*(pos.y-(tam.Y/2));
    node = IrrMngr::Inst()->addCubeSceneNode(tam,irr::video::SColor(255, 255, 255, 255));
    node->setPosition(irr::core::vector3df(pos.x,pos.y,0));
    timer = IrrMngr::Inst()->getTimer();
    time = timer->getTime();
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x, pos.y);
    bodyDef.type = b2_staticBody;
    body  = World::Inst()->GetWorld()->CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.X,tam.Y);
    fixtureDef.shape = &polyShape;
    fixtureDef.isSensor = true;
    b2Fixture* fixture = body->CreateFixture(&fixtureDef);
    b2Filter filter = fixture->GetFilterData();
    filter.categoryBits = 16;
    fixture->SetFilterData(filter);
    generar();
}
Spawner::~Spawner(){
    if(body)World::Inst()->GetWorld()->DestroyBody(body);
    if(node)node->remove();
}

void Spawner::actualiza(){
    if(!cogiendo && IrrMngr::Inst()->getTime()-time>cadencia){
        this->generar();
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
    jointDef.bodyA = body;
    jointDef.bodyB = objCogido->getBody();
    jointDef.localAnchorA.Set(0,0.3f);
    jointDef.localAnchorB.Set(0,0);
    joint = (b2RevoluteJoint*)World::Inst()->GetWorld()->CreateJoint(&jointDef);
    cogiendo = true;
}
void Spawner::soltar(){
    World::Inst()->GetWorld()->DestroyJoint(joint);
    time = timer->getTime();
    cogiendo = false;
}
void Spawner::generar(){
    switch(tipo){
        case 1: objCogido = World::Inst()->AddCogible(new Pistola(this,modelo,b2Vec2(pos.x,pos.y)));  break;
        case 2: objCogido = World::Inst()->AddCogible(new Escopeta(this,modelo,b2Vec2(pos.x,pos.y))); break;
        case 3: objCogido = World::Inst()->AddCogible(new Granada(this,modelo,b2Vec2(pos.x,pos.y)));  break;
    }
    cogiendo = true;
    this->coger(objCogido);
}
