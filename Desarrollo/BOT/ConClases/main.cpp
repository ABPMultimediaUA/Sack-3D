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
    Camera* camera = new Camera();
    std::vector<cuboMierda*>* cubos = PhysicWorld::Instance()->GetCubos();
    std::vector<Bala*>* balas = PhysicWorld::Instance()->GetBalas();
    float TimeStamp = IrrManager::Instance()->getTime();
    float DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
    //ESTA MIERDA DEBE IR FUERA
    Player* player = new Player(vector3df(40,0,0));
    Bot* bot1  = new Bot(vector3df(-80,0,0));
    Arma* arma = new Arma();
    PhysicWorld::Instance()->setPlayer(player);
    PhysicWorld::Instance()->setBot(bot1);
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
            //ESTA MIERDA DEBE IR FUERA
            player->update();
            camera->setTarget(player->getPosition());
            camera->setPosition(vector3df(player->getPosition().X,player->getPosition().Y, -100));
            arma->actualiza();
            bot1->update();
            /////////////////////////////


            IrrManager::Instance()->drawAll();
            IrrManager::Instance()->endScene();
       }
       IrrManager::Instance()->drop();
       return 0;
    }
