#include "Player.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

Player::Player(vector3df pos){
    vel = 20;
    cogiendo = false;
    puedoCoger = false;
    tam = vector3df(8, 16,4);
    node = IrrManager::Instance()->addCubeSceneNode(tam,SColor(255, 255, 124, 150));
    node->setPosition(pos);

    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;

    bodyDef.position.Set(pos.X,pos.Y);
    bodyDef.type = b2_dynamicBody;

    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    body->SetFixedRotation(true);
    polyShape.SetAsBox(tam.X/2,tam.Y/2);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0;
    fixtureDef.restitution  = 0.3f;
    fixtureDef.density  = 10.f;
    body->CreateFixture(&fixtureDef);

    polyShape.SetAsBox(32,32);
    fixtureDef.isSensor = true;
    b2Fixture* personajeSensorFixture = body->CreateFixture(&fixtureDef);
    personajeSensorFixture->SetUserData((void*)100);

    eventReceiver = IrrManager::Instance()->getEventReciever();
}

void Player::update(){
    mover();
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()* 180 / 3.14159265));
}

void Player::mover(){
    int dir = 0;
    if(eventReceiver->IsKeyDown(KEY_KEY_A))dir = -1;
    else if(eventReceiver->IsKeyDown(KEY_KEY_D))dir = 1;
    body->SetLinearVelocity(b2Vec2 (dir*vel, body->GetLinearVelocity().y));
}

void Player::saltar(){
    b2Vec2 velV = body->GetLinearVelocity();
    velV.y = vel;
    body->SetLinearVelocity(velV);
}

b2Body* Player::getBody(){
    return body;
}
vector3df Player::getPosition(){return vector3df(body->GetPosition().x,body->GetPosition().y,0);}
Player::~Player(){}
