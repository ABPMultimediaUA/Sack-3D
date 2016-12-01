#include "Player.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

Player::Player(){

    vel = 1000;
    cogiendo = false;
    puedoCoger = false;
    direccion = 1;
    salto = false;
    doblesalto = false;
    fingiendoMuerte = false;

    mesh = IrrManager::Instance()->getManager()->addCubeSceneNode(4);
    mesh->setPosition(vector3df(0,0,0));

    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;

    bodyDef.position.Set(0,0);
    bodyDef.type = b2_dynamicBody;

    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    body->SetFixedRotation(true);
    polyShape.SetAsBox(2,2);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution  = 0.3f;
    fixtureDef.density  = 100.0f;
    body->CreateFixture(&fixtureDef);

    polyShape.SetAsBox(4,4);
    fixtureDef.isSensor = true;
    b2Fixture* personajeSensorFixture = body->CreateFixture(&fixtureDef);
    personajeSensorFixture->SetUserData((void*)100);
}

void Player::update(){
    mesh->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    mesh->setRotation(vector3df(0,0,body->GetAngle()* 180 / 3.14159265));
}

void Player::mover(int dir){
    if(!fingiendoMuerte){
        b2Vec2 velV = body->GetLinearVelocity();
        velV.x = vel*dir;
        body->SetLinearVelocity(velV);
        if(dir!=0) direccion = dir;
    }
}

void Player::saltar(){
    b2Vec2 velV = body->GetLinearVelocity();
    if(!fingiendoMuerte){velV.y = vel;}else{velV.y = 10;}
    body->SetLinearVelocity(velV);
}

void Player::setSaltando(bool now){
    salto = now;
}

void Player::setDobleSaltando(bool now){
    doblesalto = now;
}

bool Player::getSaltando(){
    return salto;
}

bool Player::getDobleSaltando(){
    return doblesalto;
}

b2Body* Player::getBody(){
    return body;
}

int Player::getDireccion(){
    return direccion;
}

void Player::fingirMuerte(){
    if(!fingiendoMuerte){
        b2FixtureDef fixtureDef;
        b2CircleShape circleShape1;

        fingiendoMuerte = true;
        body->DestroyFixture(body->GetFixtureList());
        body->DestroyFixture(body->GetFixtureList());
        body->SetFixedRotation(false);
        circleShape1.m_p.Set(0,0);
        circleShape1.m_radius = 2;
        fixtureDef.shape = &circleShape1;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution  = 0.5f;
        fixtureDef.density  = 5.f;
        playerFixture = body->CreateFixture(&fixtureDef);
        playerFixture->SetUserData((void*)100);
        body->ApplyAngularImpulse(direccion);

        mesh->remove();
        mesh = IrrManager::Instance()->getManager()->addSphereSceneNode(2);
    }else{
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape polyShape;

        fingiendoMuerte = false;
        polyShape.SetAsBox(2,2);
        fixtureDef.shape = &polyShape;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution  = 0.3f;
        fixtureDef.density  = 100.0f;
        body->CreateFixture(&fixtureDef);

        polyShape.SetAsBox(4,4);
        fixtureDef.isSensor = true;
        b2Fixture* personajeSensorFixture = body->CreateFixture(&fixtureDef);
        personajeSensorFixture->SetUserData((void*)100);

        mesh->remove();
        mesh = IrrManager::Instance()->getManager()->addCubeSceneNode(4);
    }
}

Player::~Player(){}
