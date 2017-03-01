
#include "IrrManager.h"
#include "Platform.h"
#include "Escopeta.h"
#include "Teleport.h"
#include "Spawner.h"
#include "Pistola.h"
#include "Granada.h"
#include "Muelle.h"
#include "Player.h"
#include "World.h"
#include "Map.h"

enum MapLayers {
     L_PLAYER       = 1,
     L_MUELLE       = 2,
     L_TELEPORT     = 3,
     L_PLATAFORMA   = 4,
     L_ARMA         = 5,
     L_MUERTE       = 6,
     L_SPAWNER      = 7,
     L_PISTOLA      = 1,
     L_ESCOPETA     = 2,
     L_GRANADA      = 3,
};

Map::Map(irr::core::stringw file){
     int capa = 0;
     int player = 1;
     irr::io::IXMLReader* xml = IrrMngr::Inst()->createXMLReader(file);
     while (xml->read()){
          if(irr::core::stringw("objectgroup") == xml->getNodeName() && xml->getAttributeValue(L"name")){
               if     (irr::core::stringw("Spawners")     == xml->getAttributeValue(L"name")) capa = L_SPAWNER;
               else if(irr::core::stringw("Colisiones")   == xml->getAttributeValue(L"name")) capa = L_PLATAFORMA;
               else if(irr::core::stringw("Muelles")      == xml->getAttributeValue(L"name")) capa = L_MUELLE;
               else if(irr::core::stringw("Teleports")    == xml->getAttributeValue(L"name")) capa = L_TELEPORT;
               else if(irr::core::stringw("Armas")        == xml->getAttributeValue(L"name")) capa = L_ARMA;
               else if(irr::core::stringw("Players")      == xml->getAttributeValue(L"name")) capa = L_PLAYER;
               else if(irr::core::stringw("Muerte")       == xml->getAttributeValue(L"name")) capa = L_MUERTE;
          }
          else{
               int x = xml->getAttributeValueAsInt(L"x");
               int y = xml->getAttributeValueAsInt(L"y");
               int width = xml->getAttributeValueAsInt(L"width");
               int height = xml->getAttributeValueAsInt(L"height");
               if (xml->getNodeType() == irr::io::EXN_ELEMENT && irr::core::stringw("object") == xml->getNodeName()){
                    switch(capa){
                         case L_PLATAFORMA:{
                              World::Inst()->AddPlatform(new Platform(false,irr::core::vector3df(x,y,0),irr::core::vector3df(width, height, 2),irr::video::SColor(255, 186, 141, 5)));
                         break;}
                         case L_MUERTE:{
                              World::Inst()->AddPlatform(new Platform(true,irr::core::vector3df(x,y,0),irr::core::vector3df(width, height, 2),irr::video::SColor(255, 186, 141, 5)));
                         break;}
                         case L_PLAYER:{
                              World::Inst()->AddPlayer(new Player(b2Vec2(x,y),player));
                              player++;
                         break;}
                         case L_TELEPORT:{
                                   int id = 0, partner = 0;
                                   do{
                                        if(irr::core::stringw("property") == xml->getNodeName()){
                                             if     (irr::core::stringw("Id") == xml->getAttributeValue(L"name")){
                                                  id = xml->getAttributeValueAsInt(L"value");
                                             }
                                             else if(irr::core::stringw("Partner") == xml->getAttributeValue(L"name")){
                                                  partner = xml->getAttributeValueAsInt(L"value");
                                             }
                                        }
                                        xml->read();
                                   }while(irr::core::stringw("object") != xml->getNodeName());
                                   World::Inst()->AddTeleport(new Teleport(id, partner, irr::core::vector3df(x,y,0)));
                         break;}
                         case L_MUELLE:{
                                   int fuerza = 80;
                                   do{
                                        if(irr::core::stringw("property") == xml->getNodeName()){
                                             if     (irr::core::stringw("Fuerza") == xml->getAttributeValue(L"name")){
                                                  fuerza = xml->getAttributeValueAsFloat(L"value");
                                             }
                                        }
                                        xml->read();
                                   }while(irr::core::stringw("object") != xml->getNodeName());
                                   World::Inst()->AddMuelle(new Muelle(fuerza,  irr::core::vector3df(x,y,0)));
                         break;}
                         case L_ARMA:{
                              int tipo, modelo;
                              do{
                                   if(irr::core::stringw("property") == xml->getNodeName()){
                                        if     (irr::core::stringw("Tipo") == xml->getAttributeValue(L"name")){
                                             tipo = xml->getAttributeValueAsFloat(L"value");
                                        }
                                        else if(irr::core::stringw("Modelo") == xml->getAttributeValue(L"name")){
                                             modelo = xml->getAttributeValueAsFloat(L"value");
                                        }
                                   }
                                   xml->read();
                              }while(irr::core::stringw("object") != xml->getNodeName());
                              switch(tipo){
                                   case L_PISTOLA:{
                                        World::Inst()->AddCogible(new  Pistola(NULL, modelo,b2Vec2(x,y)));
                                   break;}
                                   case L_ESCOPETA:{
                                        World::Inst()->AddCogible(new Escopeta(NULL, modelo,b2Vec2(x,y)));
                                   break;}
                                   case L_GRANADA:{
                                        World::Inst()->AddCogible(new  Granada(NULL, modelo,b2Vec2(x,y)));
                                   break;}
                              }
                         break;}
                         case L_SPAWNER:{
                              int tipo, modelo;
                              do{
                                   if(irr::core::stringw("property") == xml->getNodeName()){
                                        if     (irr::core::stringw("Tipo") == xml->getAttributeValue(L"name")){
                                             tipo = xml->getAttributeValueAsFloat(L"value");
                                        }
                                        else if(irr::core::stringw("Modelo") == xml->getAttributeValue(L"name")){
                                             modelo = xml->getAttributeValueAsFloat(L"value");
                                        }
                                   }
                                   xml->read();
                              }while(irr::core::stringw("object") != xml->getNodeName());
                              World::Inst()->AddSpawner(new  Spawner(tipo,modelo,b2Vec2(x,y)));
                         break;}
                    }
               }
          }
     }
}
