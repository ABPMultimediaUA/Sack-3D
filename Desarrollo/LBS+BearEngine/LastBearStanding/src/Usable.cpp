#include "Spawner.h"
#include "Usable.h"

#define TIME2DESTROY 3000

Usable::Usable(PhysicBody* physicBody ,Spawner* expo, b2Vec2 pos, glm::vec3 tam, irr::video::SColor color)
:Cogible(physicBody,expo,pos,tam,color){
    timerCadencia = m_pBearMngr->getTimer();
    timeCadencia = 0;
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
            timer2Kill = m_pBearMngr->getTimer();
            time2Kill = timer2Kill->getTime();
            killCountDown = true;
        }
        else if(m_pBearMngr->getTime()-time2Kill>TIME2DESTROY){
            autoDestruir = true;
        }
    }
}
int  Usable::getUsos(){return usos;}
