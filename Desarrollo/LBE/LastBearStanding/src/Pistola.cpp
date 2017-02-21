#include "Pistola.h"
#include "World.h"

Pistola::Pistola(Spawner* expo, int modelo,b2Vec2 pos):Usable(expo,pos){

    idCogible = World::Inst()->GetCogibles().size();
	usos = 10;
	cadencia = 100;
    tam = irr::core::vector3df(0.4f,.2f,.02f);
    node = IrrMngr::Inst()->addCubeSceneNode(tam,irr::video::SColor(255, 0, 0, 0));
    node->setPosition(irr::core::vector3df(pos.x,pos.y,0));
    InicializeFixtures(RELEASE);
}
Pistola::~Pistola(){
    if(node){node->remove();}
}
void Pistola::usar(){
    if(usos){
        if(IrrMngr::Inst()->getTime()-timeCadencia > cadencia ){
	    	World::Inst()->AddBala(new Bala(irr::core::vector3df(body->GetPosition().x, body->GetPosition().y, 0), 300, 10, 1.0f, dir));
	    	usos--;
            timeCadencia = timerCadencia->getTime();
	    }
    }
}

int Pistola::getIdCogible(){
    return idCogible;
}
