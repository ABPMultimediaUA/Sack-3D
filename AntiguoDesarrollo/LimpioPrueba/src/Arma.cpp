/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Arma.cpp

Author:        Estudio Rorschach
Created:
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que contiene el codigo de funcionamiento para las armas.
*******************************************************************************/

#include "Arma.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

#define ARMA 30                     ///< Int para las colisiones de las armas
#define SENSORARMA 35               ///< Int para las colisiones del area cogible de las armas
#define RADTOGRAD 180 / 3.14159265  ///< Conversor de radianes a grados

/******************************************************************************
                               Arma
*******************************************************************************/

//---------------------------------------------------------------------------
/**
   Constructor
*/
Arma::Arma(){
    vector3df tam = vector3df(5,3,1);
    node = IrrManager::Instance()->addCubeSceneNode(tam,SColor(255, 255, 0, 0));
    node->setPosition(vector3df(0,0,0));
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(-100,0);
    bodyDef.type = b2_dynamicBody;

    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.X/2,tam.Y/2);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.3f;
    fixtureDef.density  = 0.f;
    b2Fixture* fixture = body->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)30);
    body->SetFixedRotation(true);
    polyShape.SetAsBox(20,20);
    fixtureDef.isSensor = true;
    b2Fixture* armaSensorFixture = body->CreateFixture(&fixtureDef);
    armaSensorFixture->SetUserData((void*)35);
}

void Arma::setCogida(bool aux){
    vector3df tam = vector3df(5,3,1);
    body->DestroyFixture(body->GetFixtureList());
    body->DestroyFixture(body->GetFixtureList());
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    b2Fixture* armaSensorFixture;
    b2Fixture* fixture;
    if(aux){
        polyShape.SetAsBox(tam.X/2,tam.Y/2);
        fixtureDef.shape = &polyShape;
        fixtureDef.isSensor = true;
        fixture = body->CreateFixture(&fixtureDef);
        fixture->SetUserData((void*)30);
        body->SetFixedRotation(true);
        polyShape.SetAsBox(20,20);
        fixtureDef.isSensor = true;
        armaSensorFixture = body->CreateFixture(&fixtureDef);
        armaSensorFixture->SetUserData((void*)35);
    }
    else{
        b2PolygonShape polyShape;
        polyShape.SetAsBox(tam.X/2,tam.Y/2);
        fixtureDef.shape = &polyShape;
        fixtureDef.friction = 10.5f;
        fixtureDef.restitution  = 0.3f;
        fixtureDef.density  = 0.f;
        fixture = body->CreateFixture(&fixtureDef);
        fixture->SetUserData((void*)30);
        body->SetFixedRotation(true);
        polyShape.SetAsBox(20,20);
        fixtureDef.isSensor = true;
        armaSensorFixture = body->CreateFixture(&fixtureDef);
        armaSensorFixture->SetUserData((void*)35);
    }
    siendoCogida = aux;
}
//---------------------------------------------------------------------------
/**
   Metodo que actualiza la posicion y rotacion del arma
*/
void Arma::actualiza(){
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()*RADTOGRAD));
}
//---------------------------------------------------------------------------
/**
   Metodo que ejecuta el usar de la clase
*/
void Arma::usar(){
    Bala* bala = new Bala(500, 1000, 100);
    b2Vec2 vel = bala->getBody()->GetLinearVelocity();
    vel.x = bala->velocidad;
    if(dir)bala->getBody()->SetLinearVelocity(vel);
    else bala->getBody()->SetLinearVelocity(-vel);
    PhysicWorld::Instance()->GetBalas()->push_back(bala);
}
//---------------------------------------------------------------------------
/**
   Getters and setters
*/
b2Body* Arma::getBody(){return body;}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Arma::~Arma(){}
