#include "Granada.h"
#include "IrrManager.h"
#include "World.h"

Granada::Granada(Spawner* expo,int modelo,b2Vec2 pos):Usable(expo,pos){
    timerIrr = IrrMngr::Inst()->getTimer();
    tam = irr::core::vector3df(.01f,.01f,.01f);
    node = IrrMngr::Inst()->addCubeSceneNode(tam,irr::video::SColor(30, 100, 30, 0));
    node->setPosition(irr::core::vector3df(pos.x,pos.y,0));
    InicializeFixtures(RELEASE);
}
Granada::~Granada(){
    if(node){node->remove();}
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
      b2Body* Partbody = World::Inst()->GetWorld()->CreateBody(&bd);

      b2CircleShape circleShape;
      circleShape.m_radius = 30.05f;

      b2FixtureDef fd;
      fd.shape = &circleShape;
      fd.density = 60;
      fd.friction = 0;
      fd.restitution = 0.99f;
      fd.filter.groupIndex = -1;

      b2Fixture* fdd = Partbody->CreateFixture(&fd);
      fdd->SetUserData((void*)DATA_PINCHO);
      particulas[i] = Partbody;
    }
    explotada = true;
  }
  if(!autoDestruir && explotada && timerIrr->getTime() - timerGranada > (mecha+100)){
    for (int i=0; i<PARTICULAS; i++){
      particulas[i]->DestroyFixture( particulas[i]->GetFixtureList());
      World::Inst()->GetWorld()->DestroyBody(particulas[i]);
    }
    autoDestruir = true;
  }
}
void Granada::usar(){
    if(usos){
      World::Inst()->getPlayer(1)->CogerTirar();
      timerGranada = timerIrr->getTime();
      usada=true;
      usos--;
    }else{CompruebaVida();}
}
