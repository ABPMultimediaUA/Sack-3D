/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Platform.cpp

Author:        Estudio Rorschach
Created:       11/11/2016 Jorge Puerto
Modified:      13/12/2016 Miguel Cordoba

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
Platform::Platform(int tipo, vector3df pos, vector3df tam,SColor color){
    mesh = IrrManager::Instance()->createCubeMesh(vector3df(pos.X, pos.Y, pos.Z),vector3df(tam.X, tam.Y,tam.Z),color);

    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;

    bodyDef.position.Set(pos.X,pos.Y);

    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    body->SetFixedRotation(true);
    polyShape.SetAsBox(tam.X/2,tam.Y/2);
    fixtureDef.shape = &polyShape;
    b2Fixture* fixture = body->CreateFixture(&fixtureDef);
    if(tipo == 2) fixture->SetUserData((void*)70);
}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Platform::~Platform(){}

