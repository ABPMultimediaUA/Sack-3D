/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Bala.cpp

Author:        Estudio Rorschach
Created:
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que contiene el codigo de funcionamiento para las balas.
*******************************************************************************/
#include "Bala.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

/******************************************************************************
                               Bala
*******************************************************************************/


//---------------------------------------------------------------------------
/**
   Constructor
*/
Bala::Bala(int tiempoVidaP, int velocidadP, int deviacionP){
    tiempoVida = tiempoVidaP;
    velocidad = velocidadP;
    desviacion = deviacionP;
    float tam = 1.5f;
    timerIrr = IrrManager::Instance()->getTimer();
    timerbala = timerIrr->getTime();
    node = IrrManager::Instance()->addCubeSceneNode(tam, SColor(255, 255,0 ,0));
    node->setPosition(vector3df(PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().x,PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().y,0));
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    int dir = PhysicWorld::Instance()->getPlayer()->getDireccion();

    bodyDef.position.Set(PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().x+(7*dir),PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().y+4);
    bodyDef.type = b2_kinematicBody;
    bodyDef.bullet = true;
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam/2,tam/2);
    fixtureDef.shape = &polyShape;

    fixtureDef.friction = 0.0f;
    fixtureDef.restitution  = 0.0f;
    fixtureDef.density  = 0.0f;
    balaFixture = body->CreateFixture(&fixtureDef);
    b2Fixture* balaSensorFixture = body->CreateFixture(&fixtureDef);

    balaSensorFixture->SetUserData((void*)40);
    b2Vec2 velo = body->GetLinearVelocity();

    if(desviacion != 0 )velo.y = (((rand()% 10000) / 10000.0)*desviacion)-(desviacion/2);
    body->SetLinearVelocity(velo);

}
//---------------------------------------------------------------------------
/**
   Actualizar
*/
void Bala::actualiza(){
    if(teletransportado) teletransportar();
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()* 180 / 3.14159265));
}
//---------------------------------------------------------------------------
/**
   Teletransporta al cubo a otra posicion
*/
void Bala::teletransportar(){
    teletransportado = false;
    nextPos.x += (1*10);
    body->SetTransform(nextPos, body->GetAngle());
}

//---------------------------------------------------------------------------
/**
   Getters y setters
*/
b2Body* Bala::getBody(){return body;}
IMeshSceneNode* Bala::getNode(){return node;}
b2Fixture* Bala::getbalaFixture(){return balaFixture;}
int Bala::getTime(){return timerbala;}
int Bala::getTimeVida(){return tiempoVida;}
void Bala::setNextPos(b2Vec2 pos){teletransportado=true; nextPos = pos;}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Bala::~Bala(){}
