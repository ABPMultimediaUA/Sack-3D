#include <iostream>
#include <irrlicht.h>
#include <Box2D/Common/b2Math.h>
#include "Player.h"
#include "PhysicWorld.h"
#include "cuboMierda.h"
#include "IrrManager.h"
#include "Platform.h"
#include "Player.h"
#include "Arma.h"

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
    std::vector<Bala*>* balas = PhysicWorld::Instance()->GetBalas();
    float TimeStamp = IrrManager::Instance()->getTime();
    float DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
    Platform(vector3df(0,-80,0),vector3df(300, 5, 40),SColor(255,0,255,0));
    //ESTA MIERDA DEBE IR FUERA
    Player* cubo1 = new Player(vector3df(0,0,0));
    Arma* arma = new Arma();
    PhysicWorld::Instance()->setPlayer(cubo1);
    PhysicWorld::Instance()->setArma(arma);
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
            //ESTA MIERDA DEBE IR FUERA
            cubo1->update();
            arma->actualiza();
            /////////////////////////////
            IrrManager::Instance()->drawAll();
            IrrManager::Instance()->endScene();
       }
       IrrManager::Instance()->drop();
       return 0;
    }
