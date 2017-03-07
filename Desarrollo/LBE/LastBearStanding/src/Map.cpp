
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

Map::Map(irr::core::stringw file){
    player = false;
    numPlayer = 0;
    playerRed = 0;
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
void Map::AddSpawner(){
     World::Inst()->AddSpawner(new  Spawner(name,type,b2Vec2(x,y)));
}
void Map::AddPlatform(){
     World::Inst()->AddPlatform(new Platform(false,b2Vec2(x,y+height),irr::core::vector3df(width, height, 2),irr::video::SColor(255, 186, 141, 5)));
}
void Map::AddMuelle(){
     World::Inst()->AddMuelle(new Muelle(type, b2Vec2(x,y)));
}
void Map::AddTeleport(){
     World::Inst()->AddTeleport(new Teleport(name, type, b2Vec2(x,y)));
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
    irr::video::SColor color;
    switch(numPlayer){
        case 0: color = irr::video::SColor(150,150, 0,0)  ; break;
        case 1: color = irr::video::SColor(150,0, 150,0)  ; break;
        case 2: color = irr::video::SColor(150,0, 0,150)  ; break;
        case 3: color = irr::video::SColor(150,150, 0,150); break;
    }
    int id = (*Client::Inst()->getIdCliente())-'0';
    if(numPlayer == id){
        std::cout<<"player "<< id<<std::endl;
        World::Inst()->AddPlayer(new Player(b2Vec2(x,y),numPlayer,color));
    }
    else if(playerRed < Client::Inst()->getNumPlayersRed()){
      std::cout<<"playerRed "<< playerRed<<std::endl;
        World::Inst()->AddPlayer(new PlayerRed(b2Vec2(x,y),numPlayer,color,Client::Inst()->playersRed[playerRed].id));
        playerRed++;
    }
    else{
      std::cout<<"NOOOO "<< playerRed<<std::endl;
    }
    numPlayer++;
}
void Map::AddPincho(){
     World::Inst()->AddPlatform(new Platform(true,b2Vec2(x,y+height),irr::core::vector3df(width, height, 2),irr::video::SColor(255, 186, 141, 5)));
}

