#include "Master.h"

#define FINPARTIDA 3000
#define FPS 1.f/30.f*1000.f

#include "World.h"
#include "BearManager.h"
#include <ctime>
#include <stdlib.h>
#include "SDL.h"

Master::Master():m_game(0){
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
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        eventReceiver.OnEvent(&e);
    }
    if(eventReceiver.IsKeyDown(SDLK_ESCAPE))SDL_Quit();
    if(SDL_GetTicks()-timeFPS>FPS){
        int fps = 1000/(SDL_GetTicks()-timeFPS);
        timeFPS = SDL_GetTicks();
        int playersVivos = World::Inst()->Update(fps,&eventReceiver);
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
    srand(time(0));
    const Num2Map * it = maps;
    while(it->num != 0){
        if(it->num == (mapList[m_game]+1)){
            World::Inst()->inicializaVariables(it->map,puntuaciones,it->num);
            m_game++;
            break;
        }
        it++;
    }
    if(it->num == 0){
        m_game=0;
        InstanciaMundo();
    }
}
bool Master::Run(){
    return !BearMngr::Inst()->IsClosed();
}
