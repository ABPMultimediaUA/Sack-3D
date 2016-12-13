/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Escopeta.cpp

Author:        Estudio Rorschach
Created:
Modified:      13/12/2016 Miguel Paniagua

Overview:
Clase que contiene el codigo de funcionamiento para las armas.
*******************************************************************************/

#include "Escopeta.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

#define ARMA 30                     ///< Int para las colisiones de las armas
#define SENSORARMA 35               ///< Int para las colisiones del area cogible de las armas
#define RADTOGRAD 180 / 3.14159265  ///< Conversor de radianes a grados

/******************************************************************************
                               Escopeta
*******************************************************************************/

//---------------------------------------------------------------------------
/**
   Constructor
*/

Escopeta::Escopeta(){

    vector3df tam = vector3df(5,3,1);
    node = IrrManager::Instance()->addCubeSceneNode(tam,SColor(255, 0, 255, 0));
    node->setPosition(vector3df(0,0,0));
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(20,0);
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
//---------------------------------------------------------------------------
/**
   Metodo que actualiza la posicion y rotacion del arma
*/
void Escopeta::actualiza(){
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()*RADTOGRAD));
}
//---------------------------------------------------------------------------
/**
   Metodo que ejecuta el usar de la clase
*/
void Escopeta::usar(){
    for(int i=0; i<10; i++){
        int desvBala = rand()% 400;
        Bala* aux = new Bala(200, 1000, desvBala);
        PhysicWorld::Instance()->GetBalas()->push_back(aux);
    }

}
//---------------------------------------------------------------------------
/**
   Getters and setters
*/
b2Body* Escopeta::getBody(){return body;}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Escopeta::~Escopeta()
{
    //dtor
}
