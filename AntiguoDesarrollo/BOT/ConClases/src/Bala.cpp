#include "Bala.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

Bala::Bala()
{
    //ctor
    tiempoVida = 1000;
    velocidad = 1000;

    timerIrr = IrrManager::Instance()->getTimer();
    timerbala = timerIrr->getTime();

    node = IrrManager::Instance()->addCubeSceneNode(8, SColor(255, 255,0 ,0));
    node->setPosition(vector3df(PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().x,PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().y,0));
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().x+20,PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().y);
    bodyDef.type = b2_kinematicBody;
    bodyDef.bullet = true;
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox(8/2,8/2);
    fixtureDef.shape = &polyShape;

    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 10.f;
    balaFixture = body->CreateFixture(&fixtureDef);

    polyShape.SetAsBox(10,10);
    fixtureDef.isSensor = true;
    b2Fixture* balaSensorFixture = body->CreateFixture(&fixtureDef);
    balaSensorFixture->SetUserData((void*)40);
}
void Bala::actualiza(){
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()* 180 / 3.14159265));
}

b2Body* Bala::getBody(){
    return body;
}

IMeshSceneNode* Bala::getNode(){
    return node;
}

b2Fixture* Bala::getbalaFixture(){
    return balaFixture;
}

int Bala::getTime()
{
        return timerbala;
}

int Bala::getTimeVida()
{
        return tiempoVida;
}

Bala::~Bala()
{
    //dtor
}
