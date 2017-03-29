
#include "PathFinding/Lista.h"
#include "PathFinding/Nodo.h"
#include "MyContactListener.h"
#include "IrrManager.h"
#include "PlayerRed.h"
#include "Teleport.h"
#include "Platform.h"
#include "Spawner.h"
#include "Cogible.h"
#include "Camera.h"
#include "Player.h"
#include "World.h"
#include "Bala.h"
#include "Bot.h"
#include "Map.h"
#include "GameObject.h"
#include "PhysicBody/PBAlivePlayer.h"

#define VELITER 6              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 6              //NUMERO DE ITERACIONES POR TICK PARA CALCULAR LA POSICION
#define TIMESTEP 0.1333f       //TIEMPO DE REFRESCO

World* World::pinstance = NULL;
World* World::Inst(){
	if(!pinstance){
    pinstance = new World;
  }
  return pinstance;
}
void World::Reset(){
  if(pinstance)delete pinstance;
  pinstance = new World;

}
World::World():m_debugMode(false){
	world.Reset(new b2World(b2Vec2(0.0f, -9.8f), true));
	contactListener.Reset(new MyContactListener);
	world.Get()->SetContactListener(contactListener.Get());
}
Lista* World::getListaNodos(){
  return m_Mapa.Get()->getListaNodos();
}
/*Lista* World::getListaSpawns(){
  return m_Mapa.Get()->getListaSpawns();
}*/
void World::inicializaVariables(irr::core::stringw mapFile,int *puntuaciones){
  m_Mapa.Reset(new Map(mapFile));
  camara.Reset(new Camera());
  for (int i = 0; i < m_Players.Size(); ++i){
    if(Bot* bot = dynamic_cast<Bot*>(m_Players.Get(i))){
      bot->InicializaVariables();
    }
  }
  TimeStamp = IrrMngr::Inst()->getTime();
  DeltaTime = IrrMngr::Inst()->getTime() - TimeStamp;
}
int World::getVivos(){
    int vivos = 0;

    for (int i = 0; i < m_Players.Size(); ++i){
      if(!m_Players.Get(i)->getMuerto())vivos++;
    }

    return vivos;
}
b2Body* World::CreateBox(int x , int y){
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(x,y);
    bodyDef.type = b2_dynamicBody;
    b2Body* body  = world.Get()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox(16,16);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 10.f;
    body->CreateFixture(&fixtureDef);
    return body;
}
Player* World::getPlayer(int mando){
  for(int i = 0; i < m_Players.Size(); ++i){
     if(m_Players.Get(i) && m_Players.Get(i)->getMando() == mando)
        return m_Players.Get(i);
  }
  return NULL;
}
int World::getGanador(){
  for (int i = 0; i < m_Players.Size(); ++i){
    if(!m_Players.Get(i)->getMuerto())return i;
  }
  return 0;
}
void  World::SwitchDebugMode(){
  if(m_debugMode){
    m_debugMode = false;
  }
  else{
    m_debugMode = true;
  }
  for (int i = 0; i < m_Nodos.Size(); ++i){
    if(m_Nodos.Get(i)){
      m_Nodos.Get(i)->SetVisible(m_debugMode);
    }
  }
}
int World::Update(int fps){
  DeltaTime = IrrMngr::Inst()->getTime() - TimeStamp;
  TimeStamp = IrrMngr::Inst()->getTime();
  IrrMngr::Inst()->beginScene();
  world.Get()->Step(TIMESTEP, VELITER, POSITER);
  world.Get()->ClearForces();
  for (int i = 0; i < m_Balas.Size(); ++i){
    if(m_Balas.Get(i)){
      m_Balas.Get(i)->actualiza();
      if(m_Balas.Get(i)->getDestruir()){
          m_Balas.Remove(i);
      }
    }
  }
  for (int i = 0; i < m_Cogibles.Size(); ++i){
    if(m_Cogibles.Get(i)){
      m_Cogibles.Get(i)->actualiza();
      if(m_Cogibles.Get(i)->getAutoDestruir()){
        m_Cogibles.Remove(i);
      }
    }
  }
  for (int i = 0; i < m_Spawners.Size(); ++i){
    if(m_Spawners.Get(i)){
      m_Spawners.Get(i)->actualiza();
    }
  }
  int players = 0;
  for (int i = 0; i < m_Players.Size(); ++i){
    if(m_Players.Get(i)){
      m_Players.Get(i)->actualiza();
    }
    if(!m_Players.Get(i)->getMuerto())players++;
  }
  camara.Get()->update(TimeStamp, fps);
  return players;
}
