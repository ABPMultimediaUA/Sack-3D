/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Player.cpp

Author:        Estudio Rorschach
Created:       11/11/2016 Jorge Puerto
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que define un player
*******************************************************************************/
#include "Player.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

#define RADTOGRAD 180 / 3.14159265  ///< Conversor de radianes a grados

/******************************************************************************
                               Player
*******************************************************************************/
//---------------------------------------------------------------------------
/**
   Constructor
*/
Player::Player(vector3df pos){
    vel = 20;
    cogiendo = false;
    puedoCoger = false;
    salto = 25;
    saltando = false;
    dobleSaltando = false;
    fingiendoMuerte = false;
    jointDef = NULL;
    direccion = 1;
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
    fixtureDef.restitution  = 0;
    fixtureDef.density  = 10.f;
    b2Fixture* fixture = body->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)10);

    polyShape.SetAsBox(tam.X/4,tam.Y/4,b2Vec2(0,-tam.Y/2), 0);
    fixtureDef.isSensor = true;
    b2Fixture* personajeSensorFixture = body->CreateFixture(&fixtureDef);
    personajeSensorFixture->SetUserData((void*)100);

    eventReceiver = IrrManager::Instance()->getEventReciever();
}
//---------------------------------------------------------------------------
/**
   Actualiza posicion y rotacion
*/
void Player::update(){
    mover();
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()* RADTOGRAD));
}
//---------------------------------------------------------------------------
/**
   Mueve
*/
void Player::mover(){
    if(!fingiendoMuerte){
        int dir = 0;
        if(eventReceiver->IsKeyDown(KEY_KEY_A))dir = -1;
        else if(eventReceiver->IsKeyDown(KEY_KEY_D))dir = 1;
        body->SetLinearVelocity(b2Vec2 (dir*vel, body->GetLinearVelocity().y));
    }
}
//---------------------------------------------------------------------------
/**
   Salta
*/
void Player::saltar(){
    if(!fingiendoMuerte){
        if(!saltando){
            b2Vec2 velV = body->GetLinearVelocity();
            velV.y = salto;
            body->SetLinearVelocity(velV);
        }
        else if(!dobleSaltando){
            b2Vec2 velV = body->GetLinearVelocity();
            velV.y = salto*3/5;
            body->SetLinearVelocity(velV);
            dobleSaltando = true;
        }
    }
}
//---------------------------------------------------------------------------
/**
   fingirMuerte
*/
void Player::fingirMuerte(){
    if(!fingiendoMuerte){
        b2FixtureDef fixtureDef;
        b2FixtureDef fixtureDef2;
        b2CircleShape circleShape1;
        b2CircleShape circleShape2;

        fingiendoMuerte = true;
        body->DestroyFixture(body->GetFixtureList());
        body->DestroyFixture(body->GetFixtureList());
        body->SetFixedRotation(false);
        circleShape1.m_p.Set(0,-3.f);
        circleShape2.m_p.Set(0,3.f);
        circleShape1.m_radius = tam.X/2;
        circleShape2.m_radius = tam.X/2;
        fixtureDef.shape = &circleShape1;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution  = 0.5f;
        fixtureDef.density  = 1.f;
        personFixture = body->CreateFixture(&fixtureDef);
        personFixture->SetUserData((void*)100);

        fixtureDef2.shape = &circleShape2;
        fixtureDef2.friction = 0.5f;
        fixtureDef2.restitution  = 0.5f;
        fixtureDef2.density  = 5.f;
        body->CreateFixture(&fixtureDef2);

        body->ApplyAngularImpulse(direccion*10000);

    }else{
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape polyShape;
        body->DestroyFixture(body->GetFixtureList());
        body->DestroyFixture(body->GetFixtureList());
        fingiendoMuerte = false;
        polyShape.SetAsBox(tam.X/2,tam.Y/2);
        fixtureDef.shape = &polyShape;
        fixtureDef.friction = 0;
        fixtureDef.restitution  = 0;
        fixtureDef.density  = 10.f;
        body->CreateFixture(&fixtureDef);

        polyShape.SetAsBox(tam.X/4,tam.Y/4,b2Vec2(0,-tam.Y/2), 0);
        fixtureDef.isSensor = true;
        b2Fixture* personajeSensorFixture = body->CreateFixture(&fixtureDef);
        personajeSensorFixture->SetUserData((void*)100);

        body->SetTransform( body->GetPosition(),0);
        body->SetAngularVelocity(0);
        body->SetFixedRotation(true);
        body->ApplyLinearImpulse(b2Vec2(0,10),b2Vec2(0,0));
    }
}
//---------------------------------------------------------------------------
/**
   crearJoint
*/
void Player::crearJoint(){
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = body;
    jointDef.bodyB = objPuedoCoger->getBody();
    //jointDef.collideConnected = false;
    //jointDef.localAnchorB = bodyPersonaje->GetLocalCenter();
    jointDef.localAnchorA.Set(0,0);
    jointDef.localAnchorB.Set(0,0);
    joint = (b2RevoluteJoint*)PhysicWorld::Instance()->GetWorld()->CreateJoint(&jointDef);
    joint->EnableMotor(true);
    joint->SetMaxMotorTorque(50.3f);
    cogiendo = true;
}
//---------------------------------------------------------------------------
/**
   romperJoint
*/
void Player::romperJoint(){
    PhysicWorld::Instance()->GetWorld()->DestroyJoint(joint);
    joint = NULL;
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x +=20;
    vel.y +=20;
    vel.x *=100;
    vel.y *=100;
    objCogido->getBody()->ApplyLinearImpulse( vel, objCogido->getBody()->GetLocalCenter());
    cogiendo = false;
    puedoCoger = false;
}
//---------------------------------------------------------------------------
/**
   usar
*/
void Player::usar(){
    dynamic_cast<Usable*>(objCogido)->usar();
}
//---------------------------------------------------------------------------
/**
   Getters y setters
*/
b2Body* Player::getBody(){return body;}
vector3df Player::getPosition(){return vector3df(body->GetPosition().x,body->GetPosition().y,0);}
bool  Player::getSaltando(){return saltando;}
void  Player::setSaltando(bool aux){saltando = aux;}
void  Player::setDobleSaltando(bool aux){dobleSaltando = aux;}
bool  Player::getCogiendo(){return cogiendo;}
int Player::getDireccion(){return direccion;}
void  Player::setCogiendo(bool aux){cogiendo = aux;}
bool  Player::getPuedoCoger(){return puedoCoger;}
void  Player::setPuedoCoger(bool aux){puedoCoger = aux;}
Cogible* Player::getObjCogido(){return objCogido;}
void  Player::setObjCogido(Cogible* aux){objCogido = aux;}
Cogible* Player::getObjPuedoCoger(){return objPuedoCoger;}
void  Player::setObjPuedoCoger(Cogible* aux){objPuedoCoger = aux;}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Player::~Player(){}
