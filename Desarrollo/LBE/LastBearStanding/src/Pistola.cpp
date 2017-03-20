#include "IrrManager.h"
#include "Pistola.h"
#include "World.h"
#include "Bala.h"

Pistola::Pistola(Spawner* expo, int modelo,b2Vec2 pos)
:Usable(expo,pos,irr::core::vector3df(0.4f,.2f,.02f),irr::video::SColor(255, 0, 0, 0)){
	usos = 10;
	cadencia = 100;
    InicializeFixtures(RELEASE);
}
Pistola::~Pistola(){}
void Pistola::usar(){
    if(usos){
        if(m_pIrrMngr->getTime()-timeCadencia > cadencia ){
            float desvBala = rand()% 3 - 3;
	    	World::Inst()->AddBala(new Bala(b2Vec2(m_pBody->GetPosition().x,-(m_pBody->GetPosition().y)), 300, 10, 0, dir,1));
	    	usos--;
            timeCadencia = timerCadencia->getTime();
	    }
    }
}
