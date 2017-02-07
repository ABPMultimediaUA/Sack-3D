
#include "PhysicWorld.h"
#include "MyContactListener.h"
#include "Cogible.h"
#include "Gets.h"
#include <iostream>

#define VELITER 6              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 6              //NUMERO DE ITERACIONES POR TICK PARA CALCULAR LA POSICION
#define TIMESTEP 1.0f / 250.0f  //TIEMPO DE REFRESCO

PhysicWorld* PhysicWorld::pinstance = NULL;
PhysicWorld* PhysicWorld::Instance(){
	if(!pinstance){
    pinstance = new PhysicWorld;
  }
  return pinstance;
}
PhysicWorld::PhysicWorld(){
	world = new b2World(b2Vec2(0.0f, -9.8f), true);
	balas = new std::vector<Bala*>();
	cogibles = new std::vector<Cogible*>();
    muelles = new std::vector<Muelle*>();
	teletransportes = new std::vector<Teleport*>();
    playersRed = new std::vector<PlayerRed*>();
	contactListener = new MyContactListener();
	world->SetContactListener(contactListener);
}
void PhysicWorld::inicializaVariables(){
  m_Players[0].Reset(new Player(b2Vec2(100,0), 1));
  //guardarDatosRed();
  GameResource<Map>(new Map("media/Map.tmx"));
  camara.Reset(new Camera());
  TimeStamp = IrrManager::Instance()->getTime();
  DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
}
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
Player* PhysicWorld::getPlayer(int mando){
    if(mando == 1) return m_Players[0].Get();
}
b2World* PhysicWorld::GetWorld(){return world;}
std::vector<Bala*>* PhysicWorld::GetBalas(){return balas;}
std::vector<Cogible*>* PhysicWorld::GetCogibles(){return cogibles;}
std::vector<Muelle*>* PhysicWorld::GetMuelles(){return muelles;}
std::vector<Teleport*>* PhysicWorld::GetTeletransportes(){return teletransportes;}
std::vector<PlayerRed*>* PhysicWorld::GetPlayersRed(){return playersRed;}
Pistola* PhysicWorld::getPistola(){return pistola;}

void PhysicWorld::setPistola(Pistola* a){pistola = a;}
void PhysicWorld::setCogibles(std::vector<Cogible*>* aux){cogibles = aux;}
void PhysicWorld::Update(){

  DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
  TimeStamp = IrrManager::Instance()->getTime();

  IrrManager::Instance()->beginScene();

  world->Step(DeltaTime*TIMESTEP, VELITER, POSITER);
  std::cout<<"Actualizandi -> "<<"HEKLFF"<<std::endl;
  world->ClearForces();

  for (int i = 0; i < MAX_NUM_BALA; ++i){
    if(m_Balas[i].Get()){
      m_Balas[i].Get()->actualiza();
      if(TimeStamp - m_Balas[i].Get()->getTime() > m_Balas[i].Get()->getTimeVida()){
          m_Balas[i].Get()->getNode()->remove();
          m_Balas[i].Get()->getBody()->DestroyFixture(m_Balas[i].Get()->getbalaFixture());
          PhysicWorld::Instance()->GetWorld()->DestroyBody(m_Balas[i].Get()->getBody());
          m_Balas[i].Reset(NULL);
      }
    }
  }
  for (int i = 0; i < MAX_NUM_PLAYER; ++i){
    if(m_Players[i].Get()){
      m_Players[i].Get()->actualiza();
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
      if(!m_Granadas[i].Get()->getAutoDestruir())
        m_Granadas[i].Get()->actualiza();
      else {
        m_Granadas[i].Reset(NULL);
      }
    }
  }
  camara.Get()->update(TimeStamp);

  for(int i=0; i < PhysicWorld::Instance()->GetPlayersRed()->size(); i++){
            PhysicWorld::Instance()->GetPlayersRed()->at(i)->actualiza();
  }
}
