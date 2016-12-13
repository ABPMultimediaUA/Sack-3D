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
Map::Map(stringw file){
    IXMLReader* xml = IrrManager::Instance()->createXMLReader(file);
    while (xml->read()){
        if (xml->getNodeType() == irr::io::EXN_ELEMENT && core::stringw("object") == xml->getNodeName()){
            int x = xml->getAttributeValueAsInt(L"x");
            int y = xml->getAttributeValueAsInt(L"y");
            int tipo = xml->getAttributeValueAsInt(L"type");
            int width = xml->getAttributeValueAsInt(L"width");
            int height = xml->getAttributeValueAsInt(L"height");
            Platform(tipo, vector3df(x+(width/2)-100,-1*(y+(height/2)),0),vector3df(width, height, rand()%10+5),SColor(255, rand()%255, rand()%255, rand()%255));
        }
    }
}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Map::~Map(){}
