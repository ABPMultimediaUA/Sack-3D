/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          cuboMierda.cpp

Author:        Estudio Rorschach
Created:
Modified:      08/12/2016 Jorge Puerto

Overview:
*******************************************************************************/

#include "cuboMierda.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

/******************************************************************************
                               cuboMierda
*******************************************************************************/


//---------------------------------------------------------------------------

cuboMierda::cuboMierda(int x, int y){
    int tam = 2;
	node = IrrManager::Instance()->addCubeSceneNode(tam, SColor(255, rand()%255, rand()%255, rand()%255));
	node->setScale(vector3df (0.07f,0.07f,0.07f));
    node->setPosition(vector3df(x,y,0));
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(x,y);
    bodyDef.type = b2_dynamicBody;
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox((tam*0.07)/2,(tam*0.07)/2);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution  = 0.5f;
    fixtureDef.density  = 2.0f;
    body->CreateFixture(&fixtureDef);

    b2Fixture* cubomierdaSensorFixture = body->CreateFixture(&fixtureDef);
    cubomierdaSensorFixture->SetUserData((void*)45);
}
//---------------------------------------------------------------------------
/**
   Teletransporta al cubo a otra posicion
*/
void cuboMierda::teletransportar(){
    teletransportado = false;
    nextPos.x += (1*10.0f/MPP);
    body->SetTransform(nextPos, body->GetAngle());
}
//---------------------------------------------------------------------------
/**
   recibe el impulso de un muelle
*/
void cuboMierda::recibeImpulso(int fuerza){
    b2Vec2 velV = body->GetLinearVelocity();
    velV.y = fuerza;
    body->SetLinearVelocity(velV);
}
/**
   actualiza
*/
void cuboMierda::actualiza(){
    if(teletransportado)teletransportar();
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()* 180 / 3.14159265));
}

/**
   Getters y setters
*/
b2Body* cuboMierda::getBody(){return body;}
void cuboMierda::setNextPos(b2Vec2 pos){teletransportado=true; nextPos = pos;}
/**
   Destructor
*/
cuboMierda::~cuboMierda(){}
