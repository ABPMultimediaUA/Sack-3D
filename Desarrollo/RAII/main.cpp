/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          main.cpp

Author:        Estudio Rorschach
Created:       08/12/2016 Jorge Puerto
Modified:      09/01/2017 Miguel Cordoba

Overview:
El maaaaaaaaain.
*******************************************************************************/

#include <irrlicht.h>
#include "PhysicWorld.h"
#include "IrrManager.h"
#include "Platform.h"
#include "Map.h"

int main(){
    PhysicWorld::Instance();
    PhysicWorld::Instance()->inicializaVariables();
    IrrManager::Instance();
    std::vector<Bala*>* balas = PhysicWorld::Instance()->GetBalas();
    float TimeStamp = IrrManager::Instance()->getTime();
    float DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
     while(IrrManager::Instance()->getDevice()->run()){
            IrrManager::Instance()->beginScene();
            DeltaTime = IrrManager::Instance()->getTime() - TimeStamp;
            TimeStamp = IrrManager::Instance()->getTime();
            PhysicWorld::Instance()->Step(DeltaTime);
            PhysicWorld::Instance()->ClearForces();
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
            PhysicWorld::Instance()->Actualiza(TimeStamp);
            IrrManager::Instance()->drawAll();
            IrrManager::Instance()->endScene();
       }
       IrrManager::Instance()->drop();
    }
