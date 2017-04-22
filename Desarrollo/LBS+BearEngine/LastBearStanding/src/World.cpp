
#include "PathFinding/Lista.h"
#include "PathFinding/Nodo.h"
#include "MyContactListener.h"
#include "BearManager.h"
#include "PlayerRed.h"
#include "Teleport.h"
#include "Metralla.h"
#include "Particle.h"
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

const int World::velocityIterations = 8;
const int World::positionIterations = 3;
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
	world.Reset(new b2World(b2Vec2(0.0f, -10.0f), false));
	contactListener.Reset(new MyContactListener);
	world.Get()->SetContactListener(contactListener.Get());
}
Lista* World::getListaNodos(){
  return m_Mapa.Get()->getListaNodos();
}
int World::getTimeMapa(){
  return m_Mapa.Get()->getTime();
}
void World::inicializaVariables(irr::core::stringw mapFile,int *puntuaciones){
  m_Mapa.Reset(new Map(mapFile));
  camara.Reset(new GameCamera());
  for (int i = 0; i < m_Players.Size(); ++i){
    if(Bot* bot = dynamic_cast<Bot*>(m_Players.Get(i))){
      bot->InicializaVariables();
    }
  }
  TimeStamp = BearMngr::Inst()->getTime();
  DeltaTime = BearMngr::Inst()->getTime() - TimeStamp;
}
Player* World::getPlayer(int mando){
  for(int i = 0; i < m_Players.Size(); ++i){
     if(m_Players.Get(i) && m_Players.Get(i)->getMando() == mando)
        return m_Players.Get(i);
  }
  return NULL;
}
int World::getVivos(){
    int vivos = 0;

    for (int i = 0; i < m_Players.Size(); ++i){
      if(!m_Players.Get(i)->getMuerto())vivos++;
    }

    return vivos;
}
int World::getGanador(){
  for (int i = 0; i < m_Players.Size(); ++i){
    if(!m_Players.Get(i)->getMuerto())return i;
  }
  return -1;
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
  DeltaTime = BearMngr::Inst()->getTime() - TimeStamp;
  TimeStamp = BearMngr::Inst()->getTime();
  BearMngr::Inst()->beginScene();
  world.Get()->Step(1.f/20.f, velocityIterations, positionIterations);
  world.Get()->ClearForces();
  UpdateBalas();
  UpdateParticles();
  UpdateMetrallas();
  UpdateCogibles();
  UpdateSpawners();
  int players;
  players = UpdatePlayers();
  camara.Get()->update(TimeStamp, fps);
  return players;
}

void World::UpdateCogibles(){
  for (int i = 0; i < m_Cogibles.Size(); ++i){
    if(m_Cogibles.Get(i)){
      m_Cogibles.Get(i)->actualiza();
      if(m_Cogibles.Get(i)->getAutoDestruir()){
        m_Cogibles.Remove(i);
      }
    }
  }
}
void World::UpdateBalas(){
  for (int i = 0; i < m_Balas.Size(); ++i){
    if(m_Balas.Get(i)){
      m_Balas.Get(i)->actualiza();
      if(m_Balas.Get(i)->getDestruir()){
          m_Balas.Remove(i);
      }
    }
  }
}
int World::UpdatePlayers(){
  int players = 0;
  for (int i = 0; i < m_Players.Size(); ++i){
    if(m_Players.Get(i)){
      m_Players.Get(i)->actualiza();
    }
    if(!m_Players.Get(i)->getMuerto())players++;
  }
  return players;
}
void World::UpdateSpawners(){
  for (int i = 0; i < m_Spawners.Size(); ++i){
    if(m_Spawners.Get(i)){
      m_Spawners.Get(i)->actualiza();
    }
  }
}
void World::UpdateMetrallas(){
  for (int i = 0; i < m_Metrallas.Size(); ++i){
    if(m_Metrallas.Get(i)){
      m_Metrallas.Get(i)->actualiza();
      if(m_Metrallas.Get(i)->getDestruir()){
          m_Metrallas.Remove(i);
      }
    }
  }
}
void World::UpdateParticles(){
  for (int i = 0; i < m_Particles.Size(); ++i){
    if(m_Particles.Get(i)){
      m_Particles.Get(i)->actualiza();
      if(m_Particles.Get(i)->getDestruir()){
          m_Particles.Remove(i);
      }
    }
  }
}
