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
     while(IrrManager::Instance()->getDevice()->run()){
            PhysicWorld::Instance()->Update();
            IrrManager::Instance()->Update();
       }
       IrrManager::Instance()->drop();
    }
