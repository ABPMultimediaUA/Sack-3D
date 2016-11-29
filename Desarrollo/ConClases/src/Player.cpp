#include "Player.h"

Player::Player(){

    mesh = IrrManager::Instance()->getManager()->addCubeSceneNode(10);
    mesh->setPosition(vector3df(0,0,0));

    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;

    bodyDef.position.Set(0,0);
    bodyDef.type = b2_dynamicBody;

    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    polyShape.SetAsBox(16/2,16/2);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.3f;
    fixtureDef.density  = 10.f;
    body->CreateFixture(&fixtureDef);
}

void Player::update(){
    mesh->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    mesh->setRotation(vector3df(0,0,body->GetAngle()* 180 / 3.14159265));
}

void Player::mover(b2Vec2 vel){
    body->SetLinearVelocity(vel);
}

Player::~Player(){}
