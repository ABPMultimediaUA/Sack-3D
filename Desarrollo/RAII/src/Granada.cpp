#include "Granada.h"
#include "PhysicWorld.h"

Granada::Granada(int modelo,b2Vec2 pos){
    timerIrr = IrrManager::Instance()->getTimer();
    timerGranada = timerIrr->getTime();
    b2BodyDef bodyDef;
    restitution = 0.2f;
    density = 2.0f;
    friction = 0.5f;
    bodyDef.position.Set(pos.x/MPP,pos.y/MPP);
    bodyDef.type = b2_dynamicBody;
    tam = irr::core::vector3df(5.f/MPP,5.f/MPP,1.f/MPP);
    node = IrrManager::Instance()->addCubeSceneNode(tam,SColor(30, 100, 30, 0));
    node->setPosition(irr::core::vector3df(pos.x/MPP,pos.y/MPP,0/MPP));
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    body->SetFixedRotation(true);
    InicializeFixtures(RELEASE);
}
void Granada::actualiza(){
    Cogible::actualiza();
    if((timerIrr->getTime() - timerGranada > mecha)&& usada){
      std::cout<<"sdfsdf"<<std::endl;
        for (int i = 0; i < PARTICULAS; i++) {
              float angle = (i / (float)PARTICULAS) * 360;
              b2Vec2 rayDir( sinf(angle), cosf(angle) );

              b2BodyDef bd;
              bd.type = b2_dynamicBody;
              bd.bullet = true; // prevent tunneling at high speed
              bd.linearDamping = 10; // drag due to moving through air
              bd.gravityScale = 0; // ignore gravity
              bd.position = body->GetPosition(); // start at blast center
              bd.linearVelocity = 500/MPP * rayDir;
              b2Body* Partbody = PhysicWorld::Instance()->GetWorld()->CreateBody(&bd);

              b2CircleShape circleShape;
              circleShape.m_radius = 30.05f/MPP; // very small

              b2FixtureDef fd;
              fd.shape = &circleShape;
              fd.density = 60; // very high - shared across all particles
              fd.friction = 0; // friction not necessary
              fd.restitution = 0.99f; // high restitution to reflect off obstacles
                /*
              fd->filter.categoryBits = 4;
              fd->filter.maskBits = 3;
                */
              fd.filter.groupIndex = -1; // particles should not collide with each other

              b2Fixture* fdd = Partbody->CreateFixture(&fd);
              fdd->SetUserData((void*)88);
              particulas[i] = Partbody;
        }
        usada = false;
        timerGranada = timerIrr->getTime();
  }
  if(usada && timerIrr->getTime() - timerGranada > (100)){
    for (int i=0; i<PARTICULAS; i++){
      particulas[i]->DestroyFixture(particulas[i]->GetFixtureList());
      particulas[i] = nullptr;
    }
  }
}
void Granada::usar(){
  PhysicWorld::Instance()->getPlayer(1)->romperJoint();
  timerGranada = timerIrr->getTime();
  usada=true;
}
