
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

const Layer2Method Map::layers[10] = {
              { L"Spawners"       , AddSpawner    }
            , { L"Colisiones"     , AddPlatform   }
            , { L"Muelles"        , AddMuelle     }
            , { L"Teleports"      , AddTeleport   }
            , { L"Armas"          , AddArma       }
            , { L"Players"        , AddPlayer     }
            , { L"Pinchos"        , AddPincho     }
            , { L"Nodos"          , AddNodo       }
            , { L"0"              , 0             }
        };

Map::Map(irr::core::stringw file){
    player = false;
    numPlayer = 0;
    playerRed = 0;
    int a=0;
    nodos.Reset(new Lista());
    irr::core::stringw layer = L"0";
    irr::io::IXMLReader* xml = IrrMngr::Inst()->createXMLReader(file);
    while (xml->read()){
        if(irr::core::stringw("imagelayer") == xml->getNodeName()){
           a=a+1;
        }
        if(irr::core::stringw("image") == xml->getNodeName() && a>0){
            const wchar_t* background;
            wchar_t backing [100]= L"media/Maps/";
            background= xml->getAttributeValue(L"source");
            background = wcscat(backing, background);
            IrrMngr::Inst()->setBackgroundImage(IrrMngr::Inst()->getDriver()->getTexture(background));
        }
        if(irr::core::stringw("objectgroup") == xml->getNodeName()){
            layer = xml->getAttributeValue(L"name");
        }
        else{
            x      = xml->getAttributeValueAsInt(L"x");
            y      = xml->getAttributeValueAsInt(L"y");
            posi   = b2Vec2(x*World::Size, y*World::Size);
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
     World::Inst()->AddSpawner(new  Spawner(name,typeInt,posi));
}
void Map::AddPlatform(){
    //posi.y=posi.y+0.1f;
    World::Inst()->AddPlatform(new Platform(false,posi, irr::core::vector3df(width*World::Size, height*World::Size, 2*World::Size),irr::video::SColor(255, 71, 33, 11)));
}
void Map::AddMuelle(){
     World::Inst()->AddMuelle(new Muelle(typeInt,posi));
}
void Map::AddTeleport(){
     World::Inst()->AddTeleport(new Teleport(name, typeInt, posi));
}
void Map::AddArma(){
    switch(name){
         case 1:{
              World::Inst()->AddCogible(new  Pistola(NULL, typeInt,posi));
         break;}
         case 2:{
              World::Inst()->AddCogible(new Escopeta(NULL, typeInt,posi));
         break;}
         case 3:{
              World::Inst()->AddCogible(new  Granada(NULL, typeInt,posi));
         break;}
    }
 }
void Map::AddPlayer(){
        irr::video::SColor color;
    switch(numPlayer){
        case 0: color = irr::video::SColor(255,54, 209, 147)  ; break;
        case 1: color = irr::video::SColor(255,225, 255, 56)  ; break;
        case 2: color = irr::video::SColor(255,255, 56, 56)  ; break;
        case 3: color = irr::video::SColor(255,255, 56, 251); break;
    }
    int id = (*Client::Inst()->getIdCliente())-'0';
    if(numPlayer == id){
      World::Inst()->AddPlayer(new Player(posi,numPlayer,color));
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
      if(numPlayer > Client::Inst()->getNumPlayersRed()){
          if(id == 0){
              char aux[30];
              sprintf(aux, "%.0f", (float)numPlayer);
              //World::Inst()->AddPlayer(new Bot(posi,numPlayer,color, aux));
          }else{
             char aux[30];
             sprintf(aux, "%.0f", (float)numPlayer);
             //World::Inst()->AddPlayer(new PlayerRed(posi,numPlayer,color, aux));
          }
      }
   }
   numPlayer++;
}
void Map::AddPincho(){
     //World::Inst()->AddPlatform(new Platform(true,posi,irr::core::vector3df(width, height, 2),irr::video::SColor(255, 186, 141, 5)));
}
void Map::AddNodo(){
    Nodo *a = World::Inst()->AddNodo(new Nodo(posi,irr::core::vector3df(1.5f, 1.f, 1)*World::Size, name, 0, NULL));
    std::string A( typeString.begin(), typeString.end() );
    std::istringstream ss(A);
    std::string token;
    while(std::getline(ss, token, ',')) {
        int integer = atoi( token.c_str() );
        a->addAdyacente(integer);
    }
    nodos.Get()->insertar(a);
}
