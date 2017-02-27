
#include "World.h"
#include "MyContactListener.h"
#include "Cogible.h"

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
World::World(){
	world.Reset(new b2World(b2Vec2(0.0f, -9.8f), true));
	contactListener.Reset(new MyContactListener);
	world.Get()->SetContactListener(contactListener.Get());
}
void World::inicializaVariables(irr::core::stringw mapFile){
  char id[30];
  GameResource<Map>(new Map(mapFile));
  for(int i=0;i<cliente->getNumPlayersRed();i++){
    World::Inst()->AddPlayer(new PlayerRed(b2Vec2(100.f, 61.995),0,cliente->playersRed[i].id));
  }
  camara.Reset(new Camera());
  TimeStamp = IrrMngr::Inst()->getTime();
  DeltaTime = IrrMngr::Inst()->getTime() - TimeStamp;
  font = IrrMngr::Inst()->getFont();
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
int World::Update(){
  DeltaTime = IrrMngr::Inst()->getTime() - TimeStamp;
  int fps = 1000/DeltaTime;
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
      if(m_Cogibles.Get(i)->getAutoDestruir())
        m_Cogibles.Remove(i);
    }
  }
  for (int i = 0; i < m_Spawners.Size(); ++i){
    if(m_Spawners.Get(i)){
      m_Spawners.Get(i)->actualiza();
    }
  }
  int players = 0;
  for (int i = 0; i < m_Players.Size(); ++i){
        //std::cout<<dynamic_cast<PlayerRed*>(m_Players.Get(i))->getId()<<std::endl;
    if(!dynamic_cast<PlayerRed*>(m_Players.Get(i))){
      m_Players.Get(i)->actualiza();
    }else{
        dynamic_cast<PlayerRed*>(m_Players.Get(i))->actualiza();
    }
    if(!m_Players.Get(i)->getMuerto())players++;
  }

  camara.Get()->update(TimeStamp, fps);
  font->draw(irr::core::stringw(fps),irr::core::rect<irr::s32>(10,10,100,60),    irr::video::SColor(255,0, 0,0));
  return players;
}
