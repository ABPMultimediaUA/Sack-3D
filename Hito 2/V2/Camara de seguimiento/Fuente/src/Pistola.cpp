#include "Pistola.h"
#include "PhysicWorld.h"

Pistola::Pistola(int modelo,b2Vec2 pos){
    b2BodyDef bodyDef;
    restitution = 0.2f;
    density = 0.2f;
    friction = 0.5f;
    bodyDef.position.Set(pos.x/MPP,pos.y/MPP);
    bodyDef.type = b2_dynamicBody;
    tam = irr::core::vector3df(5.f/MPP,3.f/MPP,1.f/MPP);
    node = IrrManager::Instance()->addCubeSceneNode(tam,SColor(255, 255, 0, 0));
    node->setPosition(irr::core::vector3df(pos.x/MPP,pos.y/MPP,0/MPP));
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    body->SetFixedRotation(true);
    InicializeFixtures(RELEASE);
}
void Pistola::usar(){
    GameResource<Bala>* balaGR = PhysicWorld::Instance()->CreateBala(
        new Bala(irr::core::vector3df(body->GetPosition().x, body->GetPosition().y, 0), 300, 2, 15.0f, dir)
    );
    Bala* bala = balaGR->Get();
    b2Vec2 vel = bala->getBody()->GetLinearVelocity();
    vel.x = bala->velocidad;
    if(dir==1) bala->getBody()->SetLinearVelocity(vel);
    else bala->getBody()->SetLinearVelocity(-vel);
    PhysicWorld::Instance()->GetBalas()->push_back(bala);
}
