#include "Map.h"
#include "IrrManager.h"
#include "Platform.h"
#include "PhysicWorld.h"
#include "GameResource.h"

#define PLAYER       1
#define MUELLE       2
#define TELEPORT     3
#define PLATAFORMA   4
#define ARMA         5
#define PISTOLA      1
#define ESCOPETA     2
#define GRANADA      3

Map::Map(irr::core::stringw file){
     int capa = 0;
     int player = 1;
     irr::io::IXMLReader* xml = IrrManager::Instance()->createXMLReader(file);
     while (xml->read()){
          if(irr::core::stringw("objectgroup") == xml->getNodeName() && xml->getAttributeValue(L"name")){
               if     (irr::core::stringw("Colisiones")   == xml->getAttributeValue(L"name")) capa = PLATAFORMA;
               else if(irr::core::stringw("Muelles")      == xml->getAttributeValue(L"name")) capa = MUELLE;
               else if(irr::core::stringw("Teleports")    == xml->getAttributeValue(L"name")) capa = TELEPORT;
               else if(irr::core::stringw("Armas")        == xml->getAttributeValue(L"name")) capa = ARMA;
               else if(irr::core::stringw("Players")      == xml->getAttributeValue(L"name")) capa = PLAYER;
          }
          else{
               int x = xml->getAttributeValueAsInt(L"x");
               int y = xml->getAttributeValueAsInt(L"y");
               int width = xml->getAttributeValueAsInt(L"width");
               int height = xml->getAttributeValueAsInt(L"height");
               if (xml->getNodeType() == irr::io::EXN_ELEMENT && irr::core::stringw("object") == xml->getNodeName()){
                    switch(capa){
                         case PLATAFORMA:{
                                   Platform(irr::core::vector3df(x+(width/2),-1*(y+(height/2)),0),irr::core::vector3df(width, height, 2),irr::video::SColor(255, 186, 141, 5));
                         break;}
                         case PLAYER:{
                                   PhysicWorld::Instance()->CreatePlayer(new Player(b2Vec2(x+(width/2),-1*(y-(height/2))),player));
                                   player++;
                         break;}
                         case TELEPORT:{
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
                                   PhysicWorld::Instance()->CreateTeleport(new Teleport(id, partner, irr::core::vector3df(x+(width/2),-1*(y-(height/2)),0)));
                         break;}
                         case MUELLE:{
                                   int fuerza = 80;
                                   do{
                                        if(irr::core::stringw("property") == xml->getNodeName()){
                                             if     (irr::core::stringw("Fuerza") == xml->getAttributeValue(L"name")){
                                                  fuerza = xml->getAttributeValueAsFloat(L"value");
                                             }
                                        }
                                        xml->read();
                                   }while(irr::core::stringw("object") != xml->getNodeName());
                                   PhysicWorld::Instance()->CreateMuelle(new Muelle(fuerza,  irr::core::vector3df(x+(width/2),-1*(y-(height/2)),0)));
                         break;}
                         case ARMA:{
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
                                   case PISTOLA:{
                                        PhysicWorld::Instance()->GetCogibles()->push_back(PhysicWorld::Instance()->CreatePistola(
                                             new Pistola(modelo,b2Vec2(x+(width/2),-1*(y-(height/2)))))->Get()
                                        );
                                   break;}
                                   case ESCOPETA:{
                                        PhysicWorld::Instance()->GetCogibles()->push_back(PhysicWorld::Instance()->CreateEscopeta(
                                             new Escopeta(modelo,b2Vec2(x+(width/2),-1*(y-(height/2)))))->Get()
                                        );
                                   break;}
                                   case GRANADA:{
                                        PhysicWorld::Instance()->GetCogibles()->push_back(PhysicWorld::Instance()->CreateGranada(
                                             new Granada(modelo,b2Vec2(x+(width/2),-1*(y-(height/2)))))->Get()
                                        );
                                   break;}
                              }
                    break;}
                    }
               }
          }
     }
}
