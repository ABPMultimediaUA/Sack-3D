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
    IrrManager::Instance()->getManager()->addCameraSceneNode(0, vector3df(0,0,-140), vector3df(0,0,0));
    std::vector<cuboMierda*>* cubos = PhysicWorld::Instance()->GetCubos();
    float TimeStamp = IrrManager::Instance()->getTime();
    float DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
    //ESTA MIERDA DEBE IR FUERA
    Player* player = new Player(vector3df(70,-40,0));
    Player* player2 = new Player(vector3df(70,40,0));
    Player* player3 = new Player(vector3df(70,00,0));
    Player* player4 = new Player(vector3df(70,-10,0));
    Player* player5 = new Player(vector3df(0,100,0));
    //Player* player6 = new Player(vector3df(100,40,0));
    //Player* player7 = new Player(vector3df(90,40,0));
    //Player* player8 = new Player(vector3df(80,40,0));
    //Player* player9 = new Player(vector3df(70,40,0));
    PhysicWorld::Instance()->setPlayer(player);
    Map* mapa = new Map("media/Map.tmx");
    b2Vec2 p1, p2; //Puntos que trazan la direccion del raycast
    ///////////////////////////
     while(IrrManager::Instance()->getDevice()->run()){
            IrrManager::Instance()->beginScene();
            DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
            TimeStamp = IrrManager::Instance()->getTime();
            PhysicWorld::Instance()->Step(DeltaTime);
            PhysicWorld::Instance()->ClearForces();
            player->update();
            player2->update();
            player3->update();
            player4->update();
            player5->update();
            //player6->update();
            //player7->update();
           // player8->update();
            //player9->update();
            IrrManager::Instance()->drawAll();
            IrrManager::Instance()->endScene();
       }
       IrrManager::Instance()->drop();
       return 0;
    }
