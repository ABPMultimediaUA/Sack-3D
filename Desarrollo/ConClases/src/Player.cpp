#include "Player.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

Player::Player(){

    vel = 40;
    cogiendo = false;
    puedoCoger = false;

    mesh = IrrManager::Instance()->getManager()->addCubeSceneNode(32);
    mesh->setPosition(vector3df(0,0,0));

    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;

    bodyDef.position.Set(0,0);
    bodyDef.type = b2_dynamicBody;

    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    body->SetFixedRotation(true);
    polyShape.SetAsBox(16,16);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.3f;
    fixtureDef.density  = 10.f;
    body->CreateFixture(&fixtureDef);

    polyShape.SetAsBox(32,32);
    fixtureDef.isSensor = true;
    b2Fixture* personajeSensorFixture = body->CreateFixture(&fixtureDef);
    personajeSensorFixture->SetUserData((void*)100);
}

void Player::update(){
    mesh->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    mesh->setRotation(vector3df(0,0,body->GetAngle()* 180 / 3.14159265));
}

void Player::mover(int dir){
    b2Vec2 velV = body->GetLinearVelocity();
    velV.x = vel*dir;
    body->SetLinearVelocity(velV);
}

void Player::saltar(){
    b2Vec2 velV = body->GetLinearVelocity();
    velV.y = vel;
    body->SetLinearVelocity(velV);
}

b2Body* Player::getBody(){
    return body;
}

Player::~Player(){}
