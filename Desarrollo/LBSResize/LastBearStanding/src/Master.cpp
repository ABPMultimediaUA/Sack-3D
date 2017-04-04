#include "Master.h"

#define FINPARTIDA 3000
#define FPS 1.f/30.f*1000.f

#include "World.h"
#include "IrrManager.h"
#include <ctime>
#include <stdlib.h>

Master::Master(){
    for (int i = 0; i < 4; ++i){
        puntuaciones[i] = 0;
    }
    finPartida = false;
    World::Inst();
    InstanciaMundo();
    IrrMngr::Inst();
    time2SyncClient = 0;
    IrrMngr::Inst()->InstanciaVariables(puntuaciones);
    timerFinPartida = IrrMngr::Inst()->getTimer();
    timerFPS = IrrMngr::Inst()->getTimer();
    timeFPS = timerFPS->getTime();
}
void Master::Update(){
    if(IrrMngr::Inst()->getTime()-timeFPS>FPS){
        int fps = 1000/(IrrMngr::Inst()->getTime()-timeFPS);
        timeFPS = timerFPS->getTime();
        int playersVivos = World::Inst()->Update(fps);
        if(!finPartida){
            if(playersVivos <= 1){
                timeFinPartida = timerFinPartida->getTime();
                finPartida = true;
            }
        }
        else if(IrrMngr::Inst()->getTime()-timeFinPartida>FINPARTIDA){
            puntuaciones[World::Inst()->getGanador()]++;
            World::Inst()->Reset();
            InstanciaMundo();
            finPartida = false;
        }
        IrrMngr::Inst()->Update();
        Client::Inst()->recibir();
        //std::cout<<"SETEO AL PLAYER "<<IrrMngr::Inst()->getTime()<<" "<<time2SyncClient<<std::endl;
        if(IrrMngr::Inst()->getTime()>(time2SyncClient+1000)){
            Client::Inst()->enviar();
            time2SyncClient = IrrMngr::Inst()->getTime();
        }
    }

}
void Master::InstanciaMundo(){
    mapList = Client::Inst()->getMaps();
    int numDeMapas =(sizeof((maps))/sizeof((maps[0]))-1);
    srand(time(0));
    const Num2Map * it = maps;
    while(it->num != 0){
        if(it->num == (mapList[game]+1)){
            World::Inst()->inicializaVariables(it->map,puntuaciones);
            game++;
            break;
        }
        it++;
    }
    if(it->num == 0){
        game=0;
        InstanciaMundo();
    }
}
bool Master::Run(){
    return IrrMngr::Inst()->getDevice()->run();
}
void Master::Drop(){
    return IrrMngr::Inst()->drop();
}
