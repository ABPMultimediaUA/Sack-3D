/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Muelle.cpp

Author:        Estudio Rorschach
Created:       12/12/2016 Miguel Cordoba
Modified:      12/12/2016 Miguel Cordoba

Overview:
Clase que define un muelle, con sus componentes grafica y fisica.

*******************************************************************************/

#include "Muelle.h"
#include "PhysicWorld.h"
#include "IrrManager.h"


/******************************************************************************
                               Muelle
*******************************************************************************/
//---------------------------------------------------------------------------
/**
   Constructor
*/
Muelle::Muelle(int f, vector3df pos, vector3df tam,SColor color){
    fuerza = f;
    mesh = IrrManager::Instance()->createCubeMesh(vector3df(pos.X, pos.Y, pos.Z),vector3df(tam.X, tam.Y,tam.Z),color);
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(pos.X,pos.Y);
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.X/2,tam.Y/2);

    b2Fixture* fixture = body->CreateFixture(&polyShape, 0.0f);
    fixture->SetUserData((void*)50);
}
/**
   Getters y setters
*/
int Muelle::getFuerza(){return fuerza;}
b2Body* Muelle::getBody(){return body;}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Muelle::~Muelle(){}

