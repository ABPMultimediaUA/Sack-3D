#include "Escopeta.h"
#include "IrrManager.h"
#include "PhysicWorld.h"

Escopeta::Escopeta(int modelo,b2Vec2 pos):Usable(pos){
    timerIrr = IrrManager::Instance()->getTimer();
    timerEscopeta = timerIrr->getTime();
    tam = irr::core::vector3df(0.7f,0.2f,0.02f);
    node = IrrManager::Instance()->addCubeSceneNode(tam,irr::video::SColor(255, 0, 255, 0));
    node->setPosition(irr::core::vector3df(pos.x,pos.y,0));
    InicializeFixtures(RELEASE);
}
void Escopeta::usar(){
    if(IrrManager::Instance()->getTime()-timerEscopeta>cadencia && conUsos){
        for(int i=0; i<15; i++){
            float desvBala = rand()% 20 - 10;
            float velBala = rand()% 3 + 10;
            GameResource<Bala>* balaGR = PhysicWorld::Instance()->CreateBala(
                new Bala(irr::core::vector3df(body->GetPosition().x, body->GetPosition().y, 0), 200, velBala, desvBala, dir, 1)
            );
        }
        timerEscopeta = timerIrr->getTime();
        usos-=1;
        if(usos==0)conUsos=false;
    }
}
