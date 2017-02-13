#include "Pistola.h"
#include "PhysicWorld.h"

Pistola::Pistola(int modelo,b2Vec2 pos):Usable(pos){
    tam = irr::core::vector3df(0.4f,.2f,.02f);
    node = IrrManager::Instance()->addCubeSceneNode(tam,irr::video::SColor(255, 0, 0, 0));
    node->setPosition(irr::core::vector3df(pos.x,pos.y,0));
    InicializeFixtures(RELEASE);
}
void Pistola::usar(){
    GameResource<Bala>* balaGR = PhysicWorld::Instance()->CreateBala(
        new Bala(irr::core::vector3df(body->GetPosition().x, body->GetPosition().y, 0), 300, 10, 1.0f, dir)
    );
   cliente->enviarDisparo();
}
