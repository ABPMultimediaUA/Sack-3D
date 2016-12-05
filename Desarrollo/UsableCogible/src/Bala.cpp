#include "Bala.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

Bala::Bala(int tvida, int vel, int desviacion)
{
    //ctor
    tiempoVida = tvida;
    velocidad = vel;
    desv = desviacion;
    int separacion=2;

    if(PhysicWorld::Instance()->getPlayer()->getDireccion() == 1){separacion = separacion;}
    else if (PhysicWorld::Instance()->getPlayer()->getDireccion() == -1){separacion = -separacion;}

    timerIrr = IrrManager::Instance()->getTimer();
    timerbala = timerIrr->getTime();

    node = IrrManager::Instance()->addCubeSceneNode(1, SColor(255, 255,0 ,0));
    node->setPosition(vector3df(PhysicWorld::Instance()->getArma()->getBody()->GetPosition().x,PhysicWorld::Instance()->getArma()->getBody()->GetPosition().y,0));
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(PhysicWorld::Instance()->getArma()->getBody()->GetPosition().x+separacion,PhysicWorld::Instance()->getArma()->getBody()->GetPosition().y);
    bodyDef.type = b2_kinematicBody;
    bodyDef.bullet = true;
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox(1,1);
    fixtureDef.shape = &polyShape;

    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 10.f;
    balaFixture = body->CreateFixture(&fixtureDef);

    polyShape.SetAsBox(2,2);
    fixtureDef.isSensor = true;
    b2Fixture* balaSensorFixture = body->CreateFixture(&fixtureDef);
    balaSensorFixture->SetUserData((void*)40);

    b2Vec2 velo = body->GetLinearVelocity();
    if(PhysicWorld::Instance()->getPlayer()->getDireccion() == 1)
    {
            velo.x = vel;
    } else if (PhysicWorld::Instance()->getPlayer()->getDireccion() == -1)
    {
            velo.x = -vel;
    }

    if(desv != 0 )velo.y = (((rand()% 10000) / 10000.0)*desv)-(desv/2);
    body->SetLinearVelocity(velo);



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
