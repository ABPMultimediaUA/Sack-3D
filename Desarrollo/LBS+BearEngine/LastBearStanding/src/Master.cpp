#include "Master.h"

#define FINPARTIDA 3000
#define FPS 1.f/30.f*1000.f

#include "World.h"
#include "BearManager.h"
#include <ctime>
#include <stdlib.h>
#include "SDL.h"
#include "Menu.h"
#include "FinPartida.h"

Master::Master():m_game(0){
    for (int i = 0; i < 4; ++i){
        puntuaciones[i] = 0;
    }
    finPartida = false;
    primeraInicializacion = true;
    estado = 0;
    BearMngr::Inst();
    time2SyncClient = 0;
    BearMngr::Inst()->InstanciaVariables(puntuaciones);
    timeFPS = SDL_GetTicks();
    menu = new Menu();
    finPartidaObject = new FinPartida();
}
void Master::Update(){
 switch(estado){
        case 0:
            //std::cout<<"ENTRAMANU"<<std::endl;
            UpdateMenu();
            if(!menu->getOn()){ estado++;}
            break;
        case 1:
            if(primeraInicializacion){
                Client::Inst()->iniciar(menu->getGameMode(), menu->getIP(), menu->getDifficult());
                InstanciaMundo();
                //IrrMngr::Inst()->InstanciaVariables(puntuaciones);
                primeraInicializacion=false;
            }else{
            UpdateGame();
            }
            break;
        case 2:
            UpdateFinPartida();
            //std::cout<<"ddd"<<std::endl;
            //std::cout<<finPartidaObject->getOn()<<std::endl;

            if(!finPartidaObject->getOn()){
                    //std::cout<<estado<<std::endl;
                    delete menu;
                    menu = NULL;
                    menu = new Menu();
                    estado=0;
                    //std::cout<<estado<<std::endl;
            }
            break;
    }
}

void Master::UpdateMenu(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        eventReceiver.OnEvent(&e);
    }
    if(SDL_GetTicks()-timeFPS>FPS){
        int fps = 1000/(SDL_GetTicks()-timeFPS);
        timeFPS = SDL_GetTicks();
        BearMngr::Inst()->Update();
        menu->update();
    }
}

void Master::UpdateGame(){
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
            if(puntuaciones[World::Inst()->getGanador()]==6){
                estado++;
                finPartidaObject->setWinner(World::Inst()->getGanador());

            }else{

            World::Inst()->Reset();
            InstanciaMundo();
            finPartida = false;}
        }
        BearMngr::Inst()->Update();
        Client::Inst()->recibir();
        //std::cout<<"falla"<<std::endl;
        if(SDL_GetTicks()>(time2SyncClient+1000)){
            Client::Inst()->enviar();
            time2SyncClient = SDL_GetTicks();
        }
    }
}

void Master::UpdateFinPartida(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        eventReceiver.OnEvent(&e);
    }
    if(SDL_GetTicks()-timeFPS>FPS){
        int fps = 1000/(SDL_GetTicks()-timeFPS);
        timeFPS = SDL_GetTicks();
        BearMngr::Inst()->Update();
        finPartidaObject->update();
    }
}

void Master::InstanciaMundo(){
    mapList = Client::Inst()->getMaps();
    srand(time(0));
    const Num2Map * it = maps;
    while(it->num != 0){
        if(it->num == (mapList[m_game]+1)){
            World::Inst()->inicializaVariables(it->map,puntuaciones,it->num);
            //std::cout<<"MAPAS: "<<it->num;
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
