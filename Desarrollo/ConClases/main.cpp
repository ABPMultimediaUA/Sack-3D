#include <iostream>
#include <irrlicht.h>
#include <Box2D/Common/b2Math.h>
#include "PhysicWorld.h"
#include "PhysicBody.h"
#include "cuboMierda.h"
#include "IrrManager.h"
#include "Platform.h"
#include "Player.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(){
    PhysicWorld::Instance();
    IrrManager::Instance();
    std::vector<cuboMierda*>* cubos = PhysicWorld::Instance()->GetCubos();
    float TimeStamp = IrrManager::Instance()->getTime();
    float DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
    Platform(vector3df(0,-80,0),vector3df(300, 5, 40),SColor(255,100,255,0));
    Player* cubo1 = new Player();
     while(IrrManager::Instance()->getDevice()->run()){
            IrrManager::Instance()->beginScene();
            DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
            TimeStamp = IrrManager::Instance()->getTime();
            PhysicWorld::Instance()->Step(DeltaTime);
            PhysicWorld::Instance()->ClearForces();
            for(int i=0; i < cubos->size(); i++){cubos->at(i)->actualiza();}
            cubo1->update();
            IrrManager::Instance()->drawAll();
            IrrManager::Instance()->endScene();
       }
       IrrManager::Instance()->drop();
       return 0;
    }
