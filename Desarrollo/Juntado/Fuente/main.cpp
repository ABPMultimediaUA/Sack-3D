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
#include "Arma.h"
#include "Escopeta.h"
#include "Granada.h"
#include "Map.h"
#include "Camera.h"
#include "Muelle.h"
#include "Teleport.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(){
    PhysicWorld::Instance();
    IrrManager::Instance();
    Camera* camera = new Camera();
    std::vector<cuboMierda*>* cubos = PhysicWorld::Instance()->GetCubos();
    std::vector<Bala*>* balas = PhysicWorld::Instance()->GetBalas();
    std::vector<Cogible*>* cogibles = PhysicWorld::Instance()->GetCogibles();
    float TimeStamp = IrrManager::Instance()->getTime();
    float DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
    //ESTA MIERDA DEBE IR FUERA
    Player* player = new Player(vector3df(120/MPP,0/MPP,0/MPP));
    //CREACION DE ARMAS//
    Arma* arma = new Arma();
    Escopeta* escopeta = new Escopeta();
    Granada* granada = new Granada();
    cogibles->push_back(arma);
    cogibles->push_back(escopeta);
    cogibles->push_back(granada);
    PhysicWorld::Instance()->setCogibles(cogibles);
    ////////////////////
    PhysicWorld::Instance()->setPlayer(player);
    PhysicWorld::Instance()->setArma(arma);
    Map* mapa = new Map("media/Map.tmx");

    Muelle* muelle1 = new Muelle(100.0f, vector3df(-210,-195,0),vector3df(10, 5, 10),SColor(255, 255, 0, 0));
    Muelle* muelle2 = new Muelle(80.0f, vector3df(-190,-195,0),vector3df(10, 5, 10),SColor(255, 0, 255, 0));
    Muelle* muelle3 = new Muelle(60.0f, vector3df(-170,-195,0),vector3df(10, 5, 10),SColor(255, 0, 0, 255));
    PhysicWorld::Instance()->GetMuelles()->push_back(muelle1);
    PhysicWorld::Instance()->GetMuelles()->push_back(muelle2);
    PhysicWorld::Instance()->GetMuelles()->push_back(muelle3);
    Teleport* portal1 = new Teleport(1, 2, vector3df(0,-187,0),vector3df(2, 20, 5),SColor(255, 255, 255, 0));
    Teleport* portal2 = new Teleport(2, 3, vector3df(50,-123,0),vector3df(2, 20, 5),SColor(255, 255, 255, 0));
    Teleport* portal3 = new Teleport(3, 1, vector3df(-6,-52,0),vector3df(2, 20, 5),SColor(255, 255, 255, 0));
    /*PhysicWorld::Instance()->GetTeletransportes()->push_back(portal1);
    PhysicWorld::Instance()->GetTeletransportes()->push_back(portal2);
    PhysicWorld::Instance()->GetTeletransportes()->push_back(portal3);*/
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
                        PhysicWorld::Instance()->GetWorld()->DestroyBody( balas->at(i)->getBody() );
                        delete balas->at(i);
                        balas->erase(balas->begin()+i);
         }
            }
            player->update();
            camera->update(TimeStamp);
            arma->actualiza();
            escopeta->actualiza();
            granada->actualiza();

            IrrManager::Instance()->drawAll();
            IrrManager::Instance()->endScene();
       }
       IrrManager::Instance()->drop();
       return 0;
    }
