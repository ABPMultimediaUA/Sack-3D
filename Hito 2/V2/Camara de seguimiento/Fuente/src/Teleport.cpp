/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Teleport.cpp

Author:        Estudio Rorschach
Created:       12/12/2016 Miguel Cordoba
Modified:      12/12/2016 Miguel Cordoba

Overview:
Clase que define un Teleport, con sus componentes grafica y fisica.

*******************************************************************************/

#include "Teleport.h"
#include "PhysicWorld.h"
#include "IrrManager.h"


/******************************************************************************
                               Teleport
*******************************************************************************/
//---------------------------------------------------------------------------
/**
   Constructor
*/
Teleport::Teleport(int i, int p, irr::core::vector3df pos, irr::core::vector3df tam ,SColor color){
    id = i;
    partner = p;
    mesh = IrrManager::Instance()->createCubeMesh(irr::core::vector3df(pos.X/MPP, pos.Y/MPP, pos.Z/MPP),irr::core::vector3df(tam.X/MPP, tam.Y/MPP,tam.Z/MPP),color);
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(pos.X/MPP,pos.Y/MPP);
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox((tam.X/2)/MPP,(tam.Y/2)/MPP);

    b2Fixture* fixture = body->CreateFixture(&polyShape, 0.0f);
    fixture->SetUserData((void*)60);
}
/**
   Getters y setters
*/
int Teleport::getTeleportId(){return id;}
int Teleport::getTeleportPartnerId(){return partner;}
b2Body* Teleport::getBody(){return body;}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Teleport::~Teleport(){}

