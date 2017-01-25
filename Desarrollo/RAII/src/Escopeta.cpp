#include "Escopeta.h"
#include "PhysicWorld.h"

Escopeta::Escopeta(int modelo,b2Vec2 pos){
    b2BodyDef bodyDef;
    restitution = 0.2f;
    density = 2.0f;
    friction = 0.5f;
    timerIrr = IrrManager::Instance()->getTimer();
    timerEscopeta = timerIrr->getTime();
    bodyDef.position.Set(pos.x/MPP,pos.y/MPP);
    bodyDef.type = b2_dynamicBody;
    tam = irr::core::vector3df(10.f/MPP,3.f/MPP,1.f/MPP);
    node = IrrManager::Instance()->addCubeSceneNode(tam,SColor(255, 0, 255, 0));
    node->setPosition(irr::core::vector3df(pos.x/MPP,pos.y/MPP,0));
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    body->SetFixedRotation(true);
    InicializeFixtures(RELEASE);
}
void Escopeta::usar(){
    if(IrrManager::Instance()->getTime()-timerEscopeta>cadencia && conUsos){
        for(int i=0; i<10; i++){
            float desvBala = rand()% 30;
            GameResource<Bala>* balaGR = PhysicWorld::Instance()->CreateBala(
                new Bala(irr::core::vector3df(body->GetPosition().x, body->GetPosition().y, 0), 100, 2, desvBala, dir)
            );
            Bala* bala = balaGR->Get();
            b2Vec2 vel = bala->getBody()->GetLinearVelocity();
            vel.x = bala->velocidad;
            if(dir==1) bala->getBody()->SetLinearVelocity(vel);
            else bala->getBody()->SetLinearVelocity(-vel);
            PhysicWorld::Instance()->GetBalas()->push_back(bala);
        }
        timerEscopeta = timerIrr->getTime();
        usos-=1;
        if(usos==0)conUsos=false;
    }
}
bool Escopeta::getConUsos(){ return conUsos;}
