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
Muelle::Muelle(float f, irr::core::vector3df pos, irr::core::vector3df tam,SColor color){
    fuerza = f/MPP;
    mesh = IrrManager::Instance()->createCubeMesh(irr::core::vector3df(pos.X/MPP, pos.Y/MPP, pos.Z/MPP),irr::core::vector3df(tam.X/MPP, tam.Y/MPP,tam.Z/MPP),color);
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(pos.X/MPP,pos.Y/MPP);
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox((tam.X/2)/MPP,(tam.Y/2)/MPP);

    b2Fixture* fixture = body->CreateFixture(&polyShape, 0.0f);
    fixture->SetUserData((void*)50);
}
/**
   Getters y setters
*/
float Muelle::getFuerza(){return fuerza;}
b2Body* Muelle::getBody(){return body;}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Muelle::~Muelle(){}

