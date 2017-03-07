#include "Spawner.h"
#include "Usable.h"

#define TIME2DESTROY 3000

Usable::Usable(Spawner* expo, b2Vec2 pos, irr::core::vector3df tam, irr::video::SColor color)
:Cogible(expo,pos,tam,color){
    timerCadencia = m_pIrrMngr->getTimer();
    usando = false;
    usos = 1;
    cadencia = 500;
    killCountDown = false;
}
Usable::~Usable(){}
void Usable::usar(){}
void Usable::actualiza(){
    Cogible::actualiza();
    if(!usos)CompruebaVida();
}
void Usable::CompruebaVida(){
    if(!cogido){
        if(!killCountDown){
            timer2Kill = m_pIrrMngr->getTimer();
            time2Kill = timer2Kill->getTime();
            killCountDown = true;
        }
        else if(m_pIrrMngr->getTime()-time2Kill>TIME2DESTROY){
            autoDestruir = true;
        }
    }
}
int  Usable::getUsos(){return usos;}
