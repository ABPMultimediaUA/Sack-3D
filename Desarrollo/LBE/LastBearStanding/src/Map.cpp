
#include "Map.h"
#include "IrrManager.h"
#include "Platform.h"
#include "World.h"
#include "GameResource.h"
#include "Spawner.h"
#include "Muelle.h"
#include "Teleport.h"
#include "Cogible.h"
#include "Pistola.h"
#include "Escopeta.h"
#include "Granada.h"

void Map::AddSpawner(){
     World::Inst()->AddSpawner(new  Spawner(name,type,b2Vec2(x,y)));
}
void Map::AddPlatform(){
     World::Inst()->AddPlatform(new Platform(false,irr::core::vector3df(x,y,0),irr::core::vector3df(width, height, 2),irr::video::SColor(255, 186, 141, 5)));
}
void Map::AddMuelle(){
     World::Inst()->AddMuelle(new Muelle(type, irr::core::vector3df(x,y,0)));
}
void Map::AddTeleport(){
     World::Inst()->AddTeleport(new Teleport(name, type, irr::core::vector3df(x,y,0)));
}
void Map::AddArma(){
     switch(name){
          case 1:{
               World::Inst()->AddCogible(new  Pistola(NULL, type,b2Vec2(x,y)));
          break;}
          case 2:{
               World::Inst()->AddCogible(new Escopeta(NULL, type,b2Vec2(x,y)));
          break;}
          case 3:{
               World::Inst()->AddCogible(new  Granada(NULL, type,b2Vec2(x,y)));
          break;}
     }
}
void Map::AddPlayer(){
     World::Inst()->AddPlayer(new Player(b2Vec2(x,y),player));
     player++;
}
void Map::AddPincho(){
     World::Inst()->AddPlatform(new Platform(true,irr::core::vector3df(x,y,0),irr::core::vector3df(width, height, 2),irr::video::SColor(255, 186, 141, 5)));
}
Map::Map(irr::core::stringw file){
     irr::core::stringw layer;
     irr::io::IXMLReader* xml = IrrMngr::Inst()->createXMLReader(file);
     while (xml->read()){
          if(irr::core::stringw("objectgroup") == xml->getNodeName()){
               layer = xml->getAttributeValue(L"name");
          }
          else{
               x      = xml->getAttributeValueAsInt(L"x");
               y      = xml->getAttributeValueAsInt(L"y");
               width  = xml->getAttributeValueAsInt(L"width");
               height = xml->getAttributeValueAsInt(L"height");
               name   = xml->getAttributeValueAsInt(L"name");
               type   = xml->getAttributeValueAsInt(L"type");
               if (irr::core::stringw("object") == xml->getNodeName()){
                    const Layer2Method * it = layers;
                    while(it->layer != L"0"){
                       if(it->layer == layer){
                           (this->*it->Layer2Method::p)();
                           break;
                       }
                       it++;
                    }
               }
          }
     }
}
