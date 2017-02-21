#include "Master.h"

#define FINPARTIDA 3000

Master::Master(){
	World::Inst();
    World::Inst()->inicializaVariables();
    IrrMngr::Inst();
    timerFinPartida = IrrMngr::Inst()->getTimer();
}
void Master::Update(){
    int playersVivos = World::Inst()->Update();
	if(!finPartida){
        if(playersVivos <= 1){
            timeFinPartida = timerFinPartida->getTime();
    		finPartida = true;
    	}
    }
    else if(IrrMngr::Inst()->getTime()-timeFinPartida>FINPARTIDA){
        World::Inst()->Reset();
        World::Inst()->inicializaVariables();
    	finPartida = false;
    }
    IrrMngr::Inst()->Update();
}
bool Master::Run(){
	return IrrMngr::Inst()->getDevice()->run();
}
void Master::Drop(){
    return IrrMngr::Inst()->drop();
}
