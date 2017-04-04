
#include "PathFinding/Lista.h"
#include "PathFinding/Nodo.h"
#include "MyContactListener.h"
#include "IrrManager.h"
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

const float World::Size = 2.f;
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
	world=new b2World(b2Vec2(0.0f, -9.8f), true);
	contactListener.Reset(new MyContactListener);
	world->SetContactListener(contactListener.Get());
}
Lista* World::getListaNodos(){
  return m_Mapa.Get()->getListaNodos();
}
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
  std::cout<<fps<<std::endl;
  DeltaTime = IrrMngr::Inst()->getTime() - TimeStamp;
  TimeStamp = IrrMngr::Inst()->getTime();
  IrrMngr::Inst()->beginScene();
  float32 timeStep = 1.0f / 30.0f;
  world->Step(timeStep, velocityIterations, positionIterations);
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
std::vector<Cogible*>   World::GetCogibles(){  return m_Cogibles.Get(); }
std::vector<Bala*>      World::GetBalas(){     return m_Balas.Get();    }
std::vector<Player*>    World::GetPlayers(){   return m_Players.Get();  }
std::vector<Teleport*>  World::GetTeleports(){ return m_Teleports.Get();}
std::vector<Muelle*>    World::GetMuelles(){   return m_Muelles.Get();  }
std::vector<Spawner*>   World::GetSpawners(){  return m_Spawners.Get(); }
std::vector<Platform*>  World::GetPlatforms(){ return m_Platforms.Get();}
std::vector<Nodo*>      World::GetNodos(){     return m_Nodos.Get();    }
std::vector<Metralla*>  World::GetMetrallas(){ return m_Metrallas.Get();}
std::vector<Particle*>  World::GetParticles(){ return m_Particles.Get();}
Cogible*  World::AddCogible (Cogible *x ) {m_Cogibles.Add(x); return x;}
Bala*     World::AddBala    (Bala *x    ) {m_Balas.Add(x);    return x;}
Teleport* World::AddTeleport(Teleport *x) {m_Teleports.Add(x);return x;}
Muelle*   World::AddMuelle  (Muelle *x  ) {m_Muelles.Add(x);  return x;}
Player*   World::AddPlayer  (Player *x  ) {m_Players.Add(x);  return x;}
Spawner*  World::AddSpawner (Spawner *x ) {m_Spawners.Add(x); return x;}
Platform* World::AddPlatform(Platform *x) {m_Platforms.Add(x);return x;}
Nodo*     World::AddNodo    (Nodo *x)     {m_Nodos.Add(x);    return x;}
Metralla* World::AddMetralla(Metralla *x) {m_Metrallas.Add(x);return x;}
Particle* World::AddParticle(Particle *x) {m_Particles.Add(x);return x;}
