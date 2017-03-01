#include "IrrManager.h"
#include "Master.h"
#include "World.h"

#define FINPARTIDA 3000
#define NUM_MAPS 2
#define FPS 1.f/30.f*1000.f

Master::Master(){
	World::Inst();
    InstanciaMundo();
    IrrMngr::Inst();
    timerFinPartida = IrrMngr::Inst()->getTimer();
    timerFPS = IrrMngr::Inst()->getTimer();
    timeFPS = timerFPS->getTime();
}
void Master::Update(){
    if(IrrMngr::Inst()->getTime()-timeFPS>FPS){
        timeFPS = timerFPS->getTime();
        int playersVivos = World::Inst()->Update();
        if(!finPartida){
            if(playersVivos <= 1){
                timeFinPartida = timerFinPartida->getTime();
                finPartida = true;
            }
        }
        else if(IrrMngr::Inst()->getTime()-timeFinPartida>FINPARTIDA){
            World::Inst()->Reset();
            InstanciaMundo();
            finPartida = false;
        }
        IrrMngr::Inst()->Update();
    }
}
void Master::InstanciaMundo(){
    int mapa = rand()%NUM_MAPS+1;
    const Num2Map * it = maps;
    while(it->num != 0){
        if(it->num == mapa){
            World::Inst()->inicializaVariables(it->map);
            break;
        }
        it++;
    }
}
bool Master::Run(){
    return IrrMngr::Inst()->getDevice()->run();
}
void Master::Drop(){
    return IrrMngr::Inst()->drop();
}
