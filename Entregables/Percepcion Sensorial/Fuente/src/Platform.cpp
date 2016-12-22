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
Platform::Platform(vector3df pos, vector3df tam,float rotation, SColor color){
    node = IrrManager::Instance()->addCubeSceneNode(vector3df(tam.X, tam.Y,tam.Z),color);
    node->setPosition(vector3df(pos.X, pos.Y, pos.Z)); 
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(pos.X,pos.Y);
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    body->SetTransform( body->GetPosition(), -rotation );
    node->setRotation(vector3df(0,0,body->GetAngle()* 180 / 3.14159265));   
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.X/2,tam.Y/2);
    body->CreateFixture(&polyShape, 0.0f);
}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Platform::~Platform(){}

