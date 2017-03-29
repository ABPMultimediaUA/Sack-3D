#include "PhysicWorld.h"
#include "MyContactListener.h"
#include "Cogible.h"

#define VELITER 8              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 8              //NUMERO DE ITERACIONES POR TICK PARA CALCULAR LA POSICION
#define TIMESTEP 1.0f / 250.0f //TIEMPO DE REFRESCO

PhysicWorld* PhysicWorld::pinstance = NULL;
PhysicWorld* PhysicWorld::Instance(){
	if(!pinstance){
    pinstance = new PhysicWorld;
  }
  return pinstance;
}
PhysicWorld::PhysicWorld(){
	world.Reset(new b2World(b2Vec2(0.0f, -9.8f), true));
	balas = new std::vector<Bala*>();
	cogibles = new std::vector<Cogible*>();
    muelles = new std::vector<Muelle*>();
	teletransportes = new std::vector<Teleport*>();
    playersRed = new std::vector<PlayerRed*>();
	contactListener = new MyContactListener();
	world.Get()->SetContactListener(contactListener);
}
void PhysicWorld::inicializaVariables(){
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
Player* PhysicWorld::getPlayer(int mando){
  for(int i = 0; i < MAX_NUM_PLAYER; ++i){
     if(m_Players[i].Get() && m_Players[i].Get()->getMando() == mando)
        return m_Players[i].Get();
  }
  return NULL;
}
void PhysicWorld::Update(){
  DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
  std::cout<<DeltaTime<<std::endl;
  TimeStamp = IrrManager::Instance()->getTime();
  IrrManager::Instance()->beginScene();
  world.Get()->Step(DeltaTime*TIMESTEP, VELITER, POSITER);
  world.Get()->ClearForces();
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
