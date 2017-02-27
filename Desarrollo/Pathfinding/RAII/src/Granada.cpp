#include "Granada.h"
#include "IrrManager.h"
#include "PhysicWorld.h"

Granada::Granada(int modelo,b2Vec2 pos):Usable(pos){
    timerIrr = IrrManager::Instance()->getTimer();
    tam = irr::core::vector3df(.01f,.01f,.01f);
    node = IrrManager::Instance()->addCubeSceneNode(tam,irr::video::SColor(30, 100, 30, 0));
    node->setPosition(irr::core::vector3df(pos.x,pos.y,0));
    InicializeFixtures(RELEASE);
}
void Granada::actualiza(){
  if(!explotada)Cogible::actualiza();
  if(timerIrr->getTime() - timerGranada > mecha && usada && !explotada){
    for (int i = 0; i < PARTICULAS; i++) {
      float angle = (i / (float)PARTICULAS) * 360;
      b2Vec2 rayDir( sinf(angle), cosf(angle) );

      b2BodyDef bd;
      bd.type = b2_dynamicBody;
      bd.bullet = true;
      bd.linearDamping = 10;
      bd.gravityScale = 0;
      bd.position = body->GetPosition();
      bd.linearVelocity = 200 * rayDir;
      b2Body* Partbody = PhysicWorld::Instance()->GetWorld()->CreateBody(&bd);

      b2CircleShape circleShape;
      circleShape.m_radius = 30.05f;

      b2FixtureDef fd;
      fd.shape = &circleShape;
      fd.density = 60;
      fd.friction = 0;
      fd.restitution = 0.99f;
      fd.filter.groupIndex = -1;

      b2Fixture* fdd = Partbody->CreateFixture(&fd);
      fdd->SetUserData((void*)88);
      particulas[i] = Partbody;
    }
    explotada = true;
  }
  if(!autoDestruir && explotada && timerIrr->getTime() - timerGranada > (mecha+100)){
    for (int i=0; i<PARTICULAS; i++){
      particulas[i]->DestroyFixture( particulas[i]->GetFixtureList());
      PhysicWorld::Instance()->GetWorld()->DestroyBody(particulas[i]);
    }
    autoDestruir = true;
  }
}
void Granada::usar(){
  PhysicWorld::Instance()->getPlayer(1)->CogerTirar();
  timerGranada = timerIrr->getTime();
  usada=true;
}
