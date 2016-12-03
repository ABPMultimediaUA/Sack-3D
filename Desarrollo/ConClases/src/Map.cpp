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
Map::Map(stringw file){
    IXMLReader* xml = IrrManager::Instance()->createXMLReader(file);
    while (xml->read()){
        if (xml->getNodeType() == irr::io::EXN_ELEMENT && core::stringw("object") == xml->getNodeName()){
            int x = xml->getAttributeValueAsInt(L"x");
            int y = xml->getAttributeValueAsInt(L"y");
            int width = xml->getAttributeValueAsInt(L"width");
            int height = xml->getAttributeValueAsInt(L"height");
            Platform(vector3df(x+(width/2)-100,-1*(y+(height/2)),0),vector3df(width, height, 40),SColor(255,100,255,0));
        }
    }
}
Map::~Map(){
}
