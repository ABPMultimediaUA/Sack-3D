
#include "Map.h"
#include "Bot.h"
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
#include "PathFinding/Nodo.h"
#include "PathFinding/Lista.h"

Map::Map(irr::core::stringw file){
    player = false;
    numPlayer = 0;
    playerRed = 0;
    nodos.Reset(new Lista());
    irr::core::stringw layer;
    irr::io::IXMLReader* xml = IrrMngr::Inst()->createXMLReader(file);
    while (xml->read()){
        if(irr::core::stringw("objectgroup") == xml->getNodeName()){
            layer = xml->getAttributeValue(L"name");
        }
        else{
            x          = xml->getAttributeValueAsInt(L"x");
            y          = xml->getAttributeValueAsInt(L"y");
            width      = xml->getAttributeValueAsInt(L"width");
            height     = xml->getAttributeValueAsInt(L"height");
            name       = xml->getAttributeValueAsInt(L"name");
            if(layer == L"Nodos")
              typeString = xml->getAttributeValue(L"type");
            else
              typeInt    = xml->getAttributeValueAsInt(L"type");
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
Lista* Map::getListaNodos(){
  return nodos.Get();
}
void Map::AddSpawner(){
     World::Inst()->AddSpawner(new  Spawner(name,typeInt,b2Vec2(x,y)));
}
void Map::AddPlatform(){
     World::Inst()->AddPlatform(new Platform(false,irr::core::vector3df(x,y,0),irr::core::vector3df(width, height, 2),irr::video::SColor(255, 186, 141, 5)));
}
void Map::AddMuelle(){
     World::Inst()->AddMuelle(new Muelle(typeInt, irr::core::vector3df(x,y,0)));
}
void Map::AddTeleport(){
     World::Inst()->AddTeleport(new Teleport(name, typeInt, irr::core::vector3df(x,y,0)));
}
void Map::AddArma(){
     switch(name){
          case 1:{
               World::Inst()->AddCogible(new  Pistola(NULL, typeInt,b2Vec2(x,y)));
          break;}
          case 2:{
               World::Inst()->AddCogible(new Escopeta(NULL, typeInt,b2Vec2(x,y)));
          break;}
          case 3:{
               World::Inst()->AddCogible(new  Granada(NULL, typeInt,b2Vec2(x,y)));
          break;}
     }
}
void Map::AddPlayer(){
    //int id = (*Client::Inst()->getIdCliente())-'0';
    //if(numPlayer == id){
    //    World::Inst()->AddPlayer(new Player(b2Vec2(x,y),numPlayer));
    //}
    //else if(playerRed < Client::Inst()->getNumPlayersRed()){
    //  std::cout<<"playerRed "<< playerRed<<std::endl;
    //    World::Inst()->AddPlayer(new PlayerRed(b2Vec2(x,y),numPlayer,Client::Inst()->playersRed[playerRed].id));
    //    playerRed++;
    //}
    int id = (*Client::Inst()->getIdCliente())-'0';
    if(numPlayer == id){
        World::Inst()->AddPlayer(new Player(b2Vec2(x,y),numPlayer));
    }
    else{
      std::cout<<"BOT "<<std::endl;
      World::Inst()->AddPlayer(new Bot(b2Vec2(x,y),numPlayer));
    }
    numPlayer++;
}
void Map::AddPincho(){
     World::Inst()->AddPlatform(new Platform(true,irr::core::vector3df(x,y,0),irr::core::vector3df(width, height, 2),irr::video::SColor(255, 186, 141, 5)));
}
void Map::AddNodo(){
    Nodo *a = World::Inst()->AddNodo(new Nodo(b2Vec2((y-2)/2, (x/2)), name, 0, NULL));
    std::string A( typeString.begin(), typeString.end() );
    std::istringstream ss(A);
    std::string token;
    while(std::getline(ss, token, ',')) {
        int integer = atoi( token.c_str() );
        a->addAdyacente(integer);
    }
    nodos.Get()->insertar(a);
}
