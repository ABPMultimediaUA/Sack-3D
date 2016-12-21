/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Map.h

Author:        Estudio Rorschach
Created:
Modified:      08/12/2016 Jorge Puerto

Overview:

*******************************************************************************/

#include "Map.h"
#include "IrrManager.h"
#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include "Platform.h"
#include "PhysicWorld.h"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/******************************************************************************
                               Map
*******************************************************************************
//---------------------------------------------------------------------------
/**
   Constructor
*/
Map::Map(int numero){
    elegirMapa(numero);
}

void Map::elegirMapa(int numero){
    numMapa = numero;
    switch (numero){
        case 1: cargarMapa("media/Map1.tmx");
        break;
        case 2: cargarMapa("media/Map2.tmx");
        break;
        case 3: cargarMapa("media/Map3.tmx");
        break;
    }
}

void Map::cargarMapa(stringw file){
    IXMLReader* xml = IrrManager::Instance()->createXMLReader(file);
    while (xml->read()){
        if (xml->getNodeType() == irr::io::EXN_ELEMENT && core::stringw("object") == xml->getNodeName()){
            int x = xml->getAttributeValueAsInt(L"x");
            int y = xml->getAttributeValueAsInt(L"y");
            int width = xml->getAttributeValueAsInt(L"width");
            int height = xml->getAttributeValueAsInt(L"height");
            //PhysicWorld::Instance()->crearPlataforma(x, y, width, height);
            Platform* p = new Platform(vector3df(x+(width/2)-100,-1*(y+(height/2)),0),
                     vector3df(width, height, 10),SColor(255, rand()%255, rand()%255, rand()%255));

            PhysicWorld::Instance()->getPlatforms()->push_back(p);
            
            //bala->getBody()->SetLinearVelocity(vel);
            //PhysicWorld::Instance()->GetBalas()->push_back(bala);



        }
    }
}

int Map::getMapa(){
  return numMapa;
}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Map::~Map(){

}
