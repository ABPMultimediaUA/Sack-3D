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
#include <math.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(){
    PhysicWorld::Instance();
    IrrManager::Instance();
    IrrManager::Instance()->getManager()->addCameraSceneNode(0, vector3df(0,0,-140), vector3df(0,0,0));
    std::vector<cuboMierda*>* cubos = PhysicWorld::Instance()->GetCubos();
    float TimeStamp = IrrManager::Instance()->getTime();
    float DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
    //ESTA MIERDA DEBE IR FUERA
    Player* player = new Player(vector3df(40,0,0));
    PhysicWorld::Instance()->setPlayer(player);
    Map* mapa = new Map("media/Map.tmx");
    float cont = 0;
    ///////////////////////////
     while(IrrManager::Instance()->getDevice()->run()){

            IrrManager::Instance()->beginScene();
            DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
            TimeStamp = IrrManager::Instance()->getTime();
            PhysicWorld::Instance()->Step(DeltaTime);
            PhysicWorld::Instance()->ClearForces();
            player->update(sin(cont),cos(cont));
            IrrManager::Instance()->drawAll();
            IrrManager::Instance()->endScene();
            cont+= 0.05f;
       }
       IrrManager::Instance()->drop();
       return 0;
    }
