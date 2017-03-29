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
Bala::Bala(vector3df pos, int tiempoVidaP, int velocidadP, int deviacionP, int dir){
    tiempoVida = tiempoVidaP;
    velocidad = velocidadP;
    desviacion = deviacionP;
    float tam = 1.5f;
    timerIrr = IrrManager::Instance()->getTimer();
    timerbala = timerIrr->getTime();
    node = IrrManager::Instance()->addCubeSceneNode(tam, SColor(255, 255,0 ,0));
    node->setPosition(pos);
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    //int dir = PhysicWorld::Instance()->getPlayer()->getDireccion();
    bodyDef.position.Set(pos.X+(7*dir),pos.Y+4);
    bodyDef.type = b2_kinematicBody;
    bodyDef.bullet = true;
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam/2,tam/2);
    fixtureDef.shape = &polyShape;

    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 10.f;
    balaFixture = body->CreateFixture(&fixtureDef);
}
//---------------------------------------------------------------------------
/**
   Actualizar
*/
void Bala::actualiza(){
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()* 180 / 3.14159265));
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
//---------------------------------------------------------------------------
/**
   Destructor
*/
Bala::~Bala(){}
