#include "Escopeta.h"
#include "IrrManager.h"
#include "World.h"

Escopeta::Escopeta(Spawner* expo, int modelo,b2Vec2 pos):Usable(expo,pos){
    usos = 5;
    tam = irr::core::vector3df(0.7f,0.2f,0.02f);
    node = IrrMngr::Inst()->addCubeSceneNode(tam,irr::video::SColor(255, 0, 255, 0));
    node->setPosition(irr::core::vector3df(pos.x,pos.y,0));
    InicializeFixtures(RELEASE);
}
Escopeta::~Escopeta(){
    if(node){node->remove();}
}
void Escopeta::usar(){
    if(usos){
        if(IrrMngr::Inst()->getTime()-timeCadencia > cadencia ){
            for(int i=0; i<10; i++){
                float desvBala = rand()% 20 - 10;
                float velBala = rand()% 3 + 10;
                World::Inst()->AddBala(new Bala(irr::core::vector3df(body->GetPosition().x, body->GetPosition().y, 0), 200, velBala, desvBala, dir, 1));
            }
            timeCadencia = timerCadencia->getTime();
            usos--;
        }
    }else{CompruebaVida();}
}
int Escopeta::getIdCogible(){
    return idCogible;
}

