#include "Escopeta.h"
#include "World.h"
#include "IrrManager.h"
#include "Bala.h"

Escopeta::Escopeta(Spawner* expo, int modelo,b2Vec2 pos)
:Usable(expo,pos,irr::core::vector3df(0.7f,0.2f,0.02f),irr::video::SColor(255, 0, 255, 0)){
    idCogible = m_pWorld->GetCogibles().size();
    usos = 5;
    InicializeFixtures(RELEASE);
}
Escopeta::~Escopeta(){}
void Escopeta::usar(){
    if(usos){
        if(m_pIrrMngr->getTime()-timeCadencia > cadencia ){
            for(int i=0; i<10; i++){
                float desvBala = rand()% 10 - 10;
                float velBala = rand()% 3 + 10;
                m_pWorld->AddBala(new Bala(b2Vec2(m_pBody->GetPosition().x,-(m_pBody->GetPosition().y)), 200, velBala, desvBala, dir, 1));
            }
            timeCadencia = timerCadencia->getTime();
            usos--;
        }
    }else{CompruebaVida();}
}
