#include "Arma.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

Arma::Arma(){
    int tam = 8;
    node = IrrManager::Instance()->addCubeSceneNode(tam, SColor(255, 0, 255, 0));
    node->setPosition(vector3df(0,0,0));
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(50,0);
    bodyDef.type = b2_dynamicBody;

    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam/2,tam/2);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.3f;
    fixtureDef.density  = 10.f;
    body->CreateFixture(&fixtureDef);
    body->SetFixedRotation(true);
    polyShape.SetAsBox(10,10);
    fixtureDef.isSensor = true;
    b2Fixture* armaSensorFixture = body->CreateFixture(&fixtureDef);
    armaSensorFixture->SetUserData((void*)30);
}

void Arma::actualiza(){
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()* 180 / 3.14159265));
}

b2Body* Arma::getBody(){
    return body;
}

Arma::~Arma()
{
    //dtor
}
