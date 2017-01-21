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
    teletransportado=false;
    vel = 40.0f/MPP;
    cogiendo = false;
    puedoCoger = false;
    salto = 50.0f/MPP;
    saltando = false;
    dobleSaltando = false;
    fingiendoMuerte = false;
    paraMorir = false;
    muerto = false;
    jointDef = NULL;
    direccion = 1;



    //tam = vector3df(8, 16,4);
    vector3df tam2 = vector3df(8, 16,4);
    tam = vector3df(tam2.X/MPP,tam2.Y/MPP,tam2.Z/MPP);
    node = IrrManager::Instance()->addCubeSceneNode(tam,SColor(255, 255, 124, 150));
    node->setPosition(pos);

    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;

    bodyDef.position.Set(pos.X,pos.Y);
    bodyDef.type = b2_dynamicBody;

    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);

    polyShape.SetAsBox(tam.X/2.0f,tam.Y/2.0f);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 7.5f;
    fixtureDef.restitution  = 0.2f;
    fixtureDef.density  = 10.0f;
    b2Fixture* fixture = body->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)10);
    body->SetFixedRotation(true);

    polyShape.SetAsBox((tam.X/4),(tam.Y));
    //polyShape.SetAsBox(tam.X/4,tam.Y/4,b2Vec2(0,-tam.Y/2), 0);
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
    //std::cout<<body->GetMass()<<std::endl;
    if(!muerto)mover();
    if(teletransportado)teletransportar();
    if(paraMorir)morir();
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
        if(eventReceiver->IsKeyDown(KEY_KEY_A)){
            direccion = dir = -1;
            body->SetLinearVelocity(b2Vec2 (dir*vel, body->GetLinearVelocity().y));}
        else if(eventReceiver->IsKeyDown(KEY_KEY_D)){
            direccion = dir = 1;
            body->SetLinearVelocity(b2Vec2 (dir*vel, body->GetLinearVelocity().y));
        }

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
            std::cout<<"salto1"<<std::endl;
        }
        else if(!dobleSaltando){
            b2Vec2 velV = body->GetLinearVelocity();
            velV.y = salto*3/4;
            body->SetLinearVelocity(velV);
            dobleSaltando = true;
             std::cout<<"salto2"<<std::endl;
        }
    }
}
//---------------------------------------------------------------------------
/**
   fingirMuerte
*/
void Player::fingirMuerte(){

    if(!fingiendoMuerte){

        if(cogiendo) romperJoint();

        std::cout<<"ENTRO1"<<std::endl;

        std::cout<<"ENTRO2"<<std::endl;
        b2FixtureDef fixtureDef;
        b2FixtureDef fixtureDef2;
        b2CircleShape circleShape1;
        b2CircleShape circleShape2;

        fingiendoMuerte = true;
        body->DestroyFixture(body->GetFixtureList());
        body->DestroyFixture(body->GetFixtureList());
        body->SetFixedRotation(false);

        circleShape1.m_p.Set(0,-3.f/MPP);
        circleShape2.m_p.Set(0,3.f/MPP);
        circleShape1.m_radius = (tam.X)/2;
        circleShape2.m_radius = (tam.X)/2;

        fixtureDef.shape = &circleShape1;

        fixtureDef.friction = 0.9f;
        fixtureDef.restitution  = 0.3f;
        fixtureDef.density  = 1.f;
        personFixture = body->CreateFixture(&fixtureDef);
        personFixture->SetUserData((void*)10);

        fixtureDef2.shape = &circleShape2;

        fixtureDef2.friction = 0.9f;
        fixtureDef2.restitution  = 0.3f;
        fixtureDef2.density  = 1.f;
        b2Fixture* personFixture2 = body->CreateFixture(&fixtureDef2);
        personFixture2->SetUserData((void*)10);

        body->SetTransform( body->GetPosition(),0);
        body->SetAngularVelocity(0);

        if(direccion == 0 )body->ApplyAngularImpulse(-1*0.0003f);
        else body->ApplyAngularImpulse(direccion*0.0003f);



    }else{
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape polyShape;

        body->DestroyFixture(body->GetFixtureList());
        body->DestroyFixture(body->GetFixtureList());
        fingiendoMuerte = false;
        body->SetFixedRotation(true);

        polyShape.SetAsBox((tam.X)/2,(tam.Y)/2);
        fixtureDef.shape = &polyShape;

        fixtureDef.friction = 7.5f;
        fixtureDef.restitution  = 0.2f;
        fixtureDef.density  = 10.0f;
        b2Fixture* fixture = body->CreateFixture(&fixtureDef);
        fixture->SetUserData((void*)10);

        polyShape.SetAsBox((tam.X)/4,(tam.Y)/4,b2Vec2(0,(-tam.Y)/2), 0);
        fixtureDef.isSensor = true;
        b2Fixture* personajeSensorFixture = body->CreateFixture(&fixtureDef);
        personajeSensorFixture->SetUserData((void*)100);

        body->SetTransform( body->GetPosition(),0);
        body->SetAngularVelocity(0);
        body->ApplyLinearImpulse(b2Vec2(0,10.0f/MPP),b2Vec2(0,0));

    }
}
//---------------------------------------------------------------------------
/**
   recibe el impulso de un muelle
*/
void Player::recibeImpulso(float fuerza){
    saltando = true;
    b2Vec2 velV = body->GetLinearVelocity();
    velV.y = fuerza;
    body->SetLinearVelocity(velV);
}
//---------------------------------------------------------------------------
/**
   Teletransporta al jugador a otra posicion
*/
void Player::teletransportar(){
    teletransportado = false;
    if(direccion != 0) nextPos.x += (direccion*10.0f/MPP);
    else nextPos.x += (1*10.0f/MPP);
    velActual = body->GetLinearVelocity();
    body->SetTransform(b2Vec2(nextPos.x,nextPos.y), body->GetAngle());
    body->SetLinearVelocity(velActual);
}
//---------------------------------------------------------------------------
/**
   Mata al personaje
*/
void Player::morir(){
    paraMorir = false;
    body->SetTransform(b2Vec2(-100,-180), body->GetAngle());
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
   // joint->SetMaxMotorTorque(50.3f);
    cogiendo = true;

    //dynamic_cast<Usable*>(PhysicWorld::Instance()->getPlayer()->getObjCogido())->setCogida(true);


}
//---------------------------------------------------------------------------
/**
   romperJoint
*/
void Player::romperJoint(){
    PhysicWorld::Instance()->GetWorld()->DestroyJoint(joint);
    joint = NULL;
    b2Vec2 velP = body->GetLinearVelocity();
    velP.x = velP.x/(MPP*450);
    velP.y = velP.y/(MPP*450);
    if(direccion==1){
    velP.x +=0.01f/MPP;
    }else if (direccion==-1){
    velP.x -=0.01f/MPP;
    }
    velP.y +=0.01f/MPP;
    //vel.x *=100;
    //vel.y *=100;
    //vel.x= vel.x * direccion;
    if(direccion==1)objCogido->getBody()->SetTransform(b2Vec2(body->GetPosition().x+(3.0f/MPP),body->GetPosition().y),0);
    if(direccion==-1)objCogido->getBody()->SetTransform(b2Vec2(body->GetPosition().x-(3.0f/MPP),body->GetPosition().y),0);
    objCogido->getBody()->ApplyLinearImpulse( velP, objCogido->getBody()->GetLocalCenter());
    cogiendo = false;
    puedoCoger = true;

    dynamic_cast<Usable*>(objCogido)->setCogida(false);
}
//---------------------------------------------------------------------------
/**
   usar
*/
void Player::usar(){
    dynamic_cast<Usable*>(objCogido)->usar();
}
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
bool Player::getMuerto(){return muerto;}
Cogible* Player::getObjCogido(){return objCogido;}
void  Player::setObjCogido(Cogible* aux){objCogido = aux;}
Cogible* Player::getObjPuedoCoger(){return objPuedoCoger;}
void  Player::setObjPuedoCoger(Cogible* aux){objPuedoCoger = aux;}
void Player::setNextPos(b2Vec2 pos){teletransportado=true; nextPos = pos;}
void Player::setParaMorir(bool aux){paraMorir = aux;}
char* Player::getServerPort(){return serverPort;
}
char* Player::getClientPort(){return clientPort;
}
char* Player::getIp(){return ip;
}

void Player::setClientPort(char aux[]){
    strncpy(clientPort, aux, sizeof(clientPort));
}
void Player::setServerPort(char aux[]){
    strncpy(serverPort, aux, sizeof(serverPort));
}
void Player::setIp(char aux[]){
    strncpy(ip, aux, sizeof(ip));
}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Player::~Player(){}
