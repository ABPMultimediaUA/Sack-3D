/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          PhysicWorld.cpp

Author:        Estudio Rorschach
Created:
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que contiene el mundo fisico, en el se trata todo lo relacionado con la fisica.
*******************************************************************************/

#include "PhysicWorld.h"
#include "MyContactListener.h"
#include "Cogible.h"

#define VELITER 10              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 10              //NUMERO DE ITERACIONES POR TICK PARA CALCULAR LA POSICION
#define TIMESTEP 1.0f / 250.0f  //TIEMPO DE REFRESCO


/******************************************************************************
                               PhysicWorld
*******************************************************************************/

//---------------------------------------------------------------------------
/**
   Instancia
*/
PhysicWorld* PhysicWorld::pinstance = 0;
PhysicWorld* PhysicWorld::Instance(){
	if(pinstance == 0){
		pinstance = new PhysicWorld;
	}
	return pinstance;
}
//---------------------------------------------------------------------------
/**
   Constructor
*/
PhysicWorld::PhysicWorld(){
	world = new b2World(b2Vec2(0.0f, -10.0f), false);
	cubos = new std::vector<cuboMierda*>();
	balas = new std::vector<Bala*>();
	cogibles = new std::vector<Cogible*>();
    muelles = new std::vector<Muelle*>();
	teletransportes = new std::vector<Teleport*>();
	contactListener = new MyContactListener();
	world->SetContactListener(contactListener);
}
//---------------------------------------------------------------------------
/**
   Genera una caja
*/
b2Body* PhysicWorld::CreateBox(int x , int y){
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(x,y);
    bodyDef.type = b2_dynamicBody;
    b2Body* body  = world->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox(16,16);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 10.f;
    body->CreateFixture(&fixtureDef);
    return body;
}
//---------------------------------------------------------------------------
/**
   Actualiza un instante en el mundo fisico
*/
void PhysicWorld::Step(float DeltaTime){ world->Step(DeltaTime*TIMESTEP, VELITER, POSITER);}
//---------------------------------------------------------------------------
/**
   ?????????????????????????????????????
*/
void PhysicWorld::ClearForces(){world->ClearForces();}
//---------------------------------------------------------------------------
/**
   Getters y setters
*/
Player* PhysicWorld::getPlayer(){return jugador1;}
b2World* PhysicWorld::GetWorld(){return world;}
std::vector<cuboMierda*>* PhysicWorld::GetCubos(){return cubos;}
std::vector<Bala*>* PhysicWorld::GetBalas(){return balas;}
std::vector<Cogible*>* PhysicWorld::GetCogibles(){return cogibles;}
std::vector<Muelle*>* PhysicWorld::GetMuelles(){return muelles;}
std::vector<Teleport*>* PhysicWorld::GetTeletransportes(){return teletransportes;}
Arma* PhysicWorld::getArma(){return arma;}
void PhysicWorld::setPlayer(Player* p){jugador1 = p;}
void PhysicWorld::setArma(Arma* a){arma = a;}
void PhysicWorld::setCogibles(std::vector<Cogible*>* aux){cogibles = aux;}
//---------------------------------------------------------------------------
/**
   Destructor
*/
PhysicWorld::~PhysicWorld(){}
