/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          PhysicWorld.cpp

Author:        Estudio Rorschach
Created:       08/12/2016 Jorge Puerto
Modified:      09/01/2017 Miguel Cordoba

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
PhysicWorld* PhysicWorld::pinstance = nullptr;
PhysicWorld* PhysicWorld::Instance(){
	if(!pinstance){
    pinstance = new PhysicWorld;
  }
  return pinstance;
}
//---------------------------------------------------------------------------
/**
   Constructor
*/
PhysicWorld::PhysicWorld(){
	world = new b2World(b2Vec2(0.0f, -30.0f/MPP), false);
	balas = new std::vector<Bala*>();
	cogibles = new std::vector<Cogible*>();
  muelles = new std::vector<Muelle*>();
	teletransportes = new std::vector<Teleport*>();
	contactListener = new MyContactListener();
	world->SetContactListener(contactListener);
}
void PhysicWorld::inicializaVariables(){
  m_Players[0].Reset(new Player(vector3df(100/MPP,0,0), 1));
  m_Players[1].Reset(new Player(vector3df(120/MPP,0,0), 2));
  GameResource<Map>(new Map("media/Map.tmx"));
  camara.Reset(new Camera());
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
Player* PhysicWorld::getPlayer(int mando){
    if(mando == 1) return m_Players[0].Get();
    else return m_Players[1].Get();
}
b2World* PhysicWorld::GetWorld(){return world;}
std::vector<Bala*>* PhysicWorld::GetBalas(){return balas;}
std::vector<Cogible*>* PhysicWorld::GetCogibles(){return cogibles;}
std::vector<Muelle*>* PhysicWorld::GetMuelles(){return muelles;}
std::vector<Teleport*>* PhysicWorld::GetTeletransportes(){return teletransportes;}
Pistola* PhysicWorld::getPistola(){return pistola;}

void PhysicWorld::setPistola(Pistola* a){pistola = a;}
void PhysicWorld::setCogibles(std::vector<Cogible*>* aux){cogibles = aux;}
void PhysicWorld::Actualiza(float TimeStamp){
  for (int i = 0; i < MAX_NUM_PLAYER; ++i){
    if(m_Players[i].Get()){
      m_Players[i].Get()->update();
    }
  }
  for (int i = 0; i < MAX_NUM_PISTOLA; ++i){
    if(m_Pistolas[i].Get()){
      m_Pistolas[i].Get()->actualiza();
    }
  }
   for (int i = 0; i < MAX_NUM_ESCOPETA; ++i){
    if(m_Escopetas[i].Get()){
      m_Escopetas[i].Get()->actualiza();
    }
  }
   for (int i = 0; i < MAX_NUM_GRANADA; ++i){
    if(m_Granadas[i].Get()){
      m_Granadas[i].Get()->actualiza();
    }
  }
  camara.Get()->update(TimeStamp);
}


//---------------------------------------------------------------------------
/**
   Destructor
*/
PhysicWorld::~PhysicWorld(){}
