
#include "Map.h"
#include "IrrManager.h"
#include "Platform.h"
#include "Spawner.h"
#include "Muelle.h"
#include "Teleport.h"
#include "Cogible.h"
#include "Pistola.h"
#include "Escopeta.h"
#include "Granada.h"
#include "Bot.h"
#include "PathFinding/Nodo.h"
#include "PathFinding/Lista.h"
#include "GameObject.h"
#include "PhysicBody/PBDeadPlayer.h"

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
            x      = xml->getAttributeValueAsInt(L"x");
            y      = xml->getAttributeValueAsInt(L"y");
            width  = xml->getAttributeValueAsInt(L"width");
            height = xml->getAttributeValueAsInt(L"height");
            name   = xml->getAttributeValueAsInt(L"name");
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
    World::Inst()->AddPlatform(new Platform(false,b2Vec2(x,y+height),irr::core::vector3df(width, height, 2),irr::video::SColor(255, 186, 141, 5)));
}
void Map::AddMuelle(){
     World::Inst()->AddMuelle(new Muelle(typeInt, b2Vec2(x,y)));
}
void Map::AddTeleport(){
     World::Inst()->AddTeleport(new Teleport(name, typeInt, b2Vec2(x,y)));
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
        irr::video::SColor color;
    switch(numPlayer){
        case 0: color = irr::video::SColor(255,255, 0,0)  ; break;
        case 1: color = irr::video::SColor(255,0, 255,0)  ; break;
        case 2: color = irr::video::SColor(255,0, 0,255)  ; break;
        case 3: color = irr::video::SColor(255,255, 0,255); break;
    }
    int id = (*Client::Inst()->getIdCliente())-'0';
    if(numPlayer == id){
      World::Inst()->AddPlayer(new Player(b2Vec2(x,y),numPlayer,color));
   }
   if(playerRed < Client::Inst()->getNumPlayersRed()){
       for(int i=0;i<Client::Inst()->getNumPlayersRed()&&playerRed<Client::Inst()->getNumPlayersRed();i++){
        if(numPlayer==(*Client::Inst()->playersRed[i].id)-'0'){
        World::Inst()->AddPlayer(new PlayerRed(b2Vec2(x,y),(*Client::Inst()->playersRed[i].id)-'0',color, Client::Inst()->playersRed[i].id));
        playerRed++;
        }
      }
   }
   else{
        //if(numPlayer > Client::Inst()->getNumPlayersRed()){
        //    if(id == 0){
        //        char aux[30];
        //        sprintf(aux, "%.0f", (float)numPlayer);
        //        World::Inst()->AddPlayer(new Bot(b2Vec2(x,y),numPlayer,color, aux));
        //    }else{
        //       char aux[30];
        //       sprintf(aux, "%.0f", (float)numPlayer);
        //       World::Inst()->AddPlayer(new PlayerRed(b2Vec2(x,y),numPlayer,color, aux));
        //    }
        //}
   }
   numPlayer++;
}
void Map::AddPincho(){
     World::Inst()->AddPlatform(new Platform(true,b2Vec2(x,y+height),irr::core::vector3df(width, height, 2),irr::video::SColor(255, 186, 141, 5)));
}
void Map::AddNodo(){
    Nodo *a = World::Inst()->AddNodo(new Nodo(b2Vec2(x,y),irr::core::vector3df(1.5, height, 10), name, 0, NULL));
    std::string A( typeString.begin(), typeString.end() );
    std::istringstream ss(A);
    std::string token;
    while(std::getline(ss, token, ',')) {
        int integer = atoi( token.c_str() );
        a->addAdyacente(integer);
    }
    nodos.Get()->insertar(a);
}

