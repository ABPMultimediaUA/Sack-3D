/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Platform.cpp

Author:        Estudio Rorschach
Created:       11/11/2016 Jorge Puerto
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que define una plataforma, con sus componentes grafica y fisica.

*******************************************************************************/

#include "Platform.h"
#include "PhysicWorld.h"
#include "IrrManager.h"


/******************************************************************************
                               Platform
*******************************************************************************/
//---------------------------------------------------------------------------
/**
   Constructor
*/
Platform::Platform(irr::core::vector3df pos, irr::core::vector3df tam,SColor color){
    mesh = IrrManager::Instance()->createCubeMesh(irr::core::vector3df(pos.X/MPP, pos.Y/MPP, pos.Z/MPP),irr::core::vector3df(tam.X/MPP, tam.Y/MPP,tam.Z/MPP),color);
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(pos.X/MPP,pos.Y/MPP);
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox((tam.X/2)/MPP,(tam.Y/2)/MPP);
    body->CreateFixture(&polyShape, 0.0f);
}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Platform::~Platform(){}

