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
#include "Map.h"
#include "Camera.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(){
    PhysicWorld::Instance();
    IrrManager::Instance();
    IrrManager::Instance()->getManager()->addCameraSceneNode(0, vector3df(220,-130,-190), vector3df(220,-130,0));
    float TimeStamp = IrrManager::Instance()->getTime();
    float DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
    //ESTA MIERDA DEBE IR FUERA
    Player* coche = new Player(vector3df(15,-15,0));
    Player* objetivo = new Player(vector3df(15,-55,0));
    Map* mapa = new Map("media/Map.tmx");
    PhysicWorld::Instance()->setMapa(mapa);
    PhysicWorld::Instance()->setPlayers(coche, objetivo);

    ///////////////////////////
     while(IrrManager::Instance()->getDevice()->run()){
            IrrManager::Instance()->beginScene();
            DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
            TimeStamp = IrrManager::Instance()->getTime();
            PhysicWorld::Instance()->Step(DeltaTime);
            PhysicWorld::Instance()->ClearForces();
            coche->update();
            objetivo->update();
            IrrManager::Instance()->drawAll();
            IrrManager::Instance()->endScene();
       }
       IrrManager::Instance()->drop();
       return 0;
    }
