#include "Master.h"

#define FINPARTIDA 3000
#define FPS 1.f/30.f*1000.f

#include "World.h"
#include "BearManager.h"
#include <ctime>
#include <stdlib.h>
#include "SDL.h"

Master::Master(){
    for (int i = 0; i < 4; ++i){
        puntuaciones[i] = 0;
    }
    finPartida = false;
    World::Inst();
    InstanciaMundo();
    BearMngr::Inst();
    time2SyncClient = 0;
    BearMngr::Inst()->InstanciaVariables(puntuaciones);
    timeFPS = SDL_GetTicks();
}
void Master::Update(){
    if(SDL_GetTicks()-timeFPS>FPS){
        int fps = 1000/(SDL_GetTicks()-timeFPS);
        timeFPS = SDL_GetTicks();
        int playersVivos = World::Inst()->Update(fps);
        if(!finPartida){
            if(playersVivos <= 1){
                timeFinPartida = SDL_GetTicks();
                finPartida = true;
            }
        }
        else if(SDL_GetTicks()-timeFinPartida>FINPARTIDA){
            puntuaciones[World::Inst()->getGanador()]++;
            World::Inst()->Reset();
            InstanciaMundo();
            finPartida = false;
        }
        BearMngr::Inst()->Update();
        Client::Inst()->recibir();
        if(SDL_GetTicks()>(time2SyncClient+1000)){
            Client::Inst()->enviar();
            time2SyncClient = SDL_GetTicks();
        }
    }

}
void Master::InstanciaMundo(){
    mapList = Client::Inst()->getMaps();
    int numDeMapas =(sizeof((maps))/sizeof((maps[0]))-1);
    srand(time(0));
    const Num2Map * it = maps;
    //std::cout<<"MAPS "<<mapList[0]<<" "<<mapList[1]<<mapList[2]<<mapList[3]<<mapList[4]<<mapList[5]<<std::endl;
    while(it->num != 0){
        if(it->num == (mapList[game]+1)){
            //std::cout<<"MAP "<<mapList[game]+1<<std::endl;
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
    BearMngr::Inst()->getDevice()->run();
    return !BearMngr::Inst()->IsClosed();
}
