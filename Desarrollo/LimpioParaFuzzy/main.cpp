/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          main.cpp

Author:        Estudio Rorschach
Created:
Modified:      08/12/2016 Jorge Puerto

Overview:
El maaaaaaaaain.
*******************************************************************************/

#include <iostream>
#include <irrlicht.h>
#include <Box2D/Common/b2Math.h>
#include "Player.h"
#include "PhysicWorld.h"
#include "cuboMierda.h"
#include "IrrManager.h"
#include "Platform.h"
#include "Bot.h"
#include "Arma.h"
#include "Escopeta.h"
#include "Granada.h"
#include "Map.h"
#include "Camera.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(){
    //PhysicWorld::Instance();
    //IrrManager::Instance();
    Camera* camera = new Camera();
    std::vector<cuboMierda*>* cubos = PhysicWorld::Instance()->GetCubos();
    std::vector<Bala*>* balas = PhysicWorld::Instance()->GetBalas();
    std::vector<Cogible*>* cogibles = PhysicWorld::Instance()->GetCogibles();
    float TimeStamp = IrrManager::Instance()->getTime();
    float DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
    //ESTA MIERDA DEBE IR FUERA
    Player* player = new Player(vector3df(-200,-190,0));
    //Bot* bot1  = new Bot(vector3df(100,-20,0));
    //CREACION DE ARMAS//

    Arma* arma = new Arma(vector3df(-320,-20,0));
    Escopeta* escopeta = new Escopeta(vector3df(180,-20,0));

    cogibles->push_back(arma);
    cogibles->push_back(escopeta);
    PhysicWorld::Instance()->setCogibles(cogibles);
    ////////////////////
    PhysicWorld::Instance()->setPlayer(player);
    //PhysicWorld::Instance()->setBot(bot1);
    PhysicWorld::Instance()->setArma(arma);
    Map* mapa = new Map("media/Map.tmx");
    ///////////////////////////
     while(IrrManager::Instance()->getDevice()->run()){
            IrrManager::Instance()->beginScene();
            DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
            TimeStamp = IrrManager::Instance()->getTime();
            PhysicWorld::Instance()->Step(DeltaTime);
            PhysicWorld::Instance()->ClearForces();
            for(int i=0; i < cubos->size(); i++){cubos->at(i)->actualiza();}
            for(int i=0; i < balas->size(); i++){
                    balas->at(i)->actualiza();
                     if(TimeStamp - balas->at(i)->getTime() > balas->at(i)->getTimeVida()){
                        balas->at(i)->getNode()->remove();
                        balas->at(i)->getBody()->DestroyFixture(balas->at(i)->getbalaFixture());
                        balas->erase(balas->begin()+i);
                    }
            }
            player->update();
            camera->update(TimeStamp);
            arma->actualiza();
            escopeta->actualiza();
            //bot1->update();


            IrrManager::Instance()->drawAll();
            IrrManager::Instance()->endScene();
       }
       IrrManager::Instance()->drop();
       return 0;
    }
