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

/******************************************************************************
                               Map
*******************************************************************************
//---------------------------------------------------------------------------
/**
   Constructor
*/
Map::Map(stringw file){
     int capa = 0;
     IXMLReader* xml = IrrManager::Instance()->createXMLReader(file);
     while (xml->read()){
          if(core::stringw("objectgroup") == xml->getNodeName() && xml->getAttributeValue(L"name")){
               if     (core::stringw("Colisiones") == xml->getAttributeValue(L"name")) capa = PLATAFORMA;
               else if(core::stringw("Muelle")     == xml->getAttributeValue(L"name")) capa = MUELLE;
               else if(core::stringw("Teleport")   == xml->getAttributeValue(L"name")) capa = TELEPORT;
               else if(core::stringw("Armas")      == xml->getAttributeValue(L"name")) capa = ARMA;
          }
          else{
               int x = xml->getAttributeValueAsInt(L"x");
               int y = xml->getAttributeValueAsInt(L"y");
               int width = xml->getAttributeValueAsInt(L"width");
               int height = xml->getAttributeValueAsInt(L"height");
               if (xml->getNodeType() == irr::io::EXN_ELEMENT && core::stringw("object") == xml->getNodeName()){
                    switch(capa){
                         case PLATAFORMA:{
                                   Platform(irr::core::vector3df(x+(width/2)-100,-1*(y+(height/2)),0),irr::core::vector3df(width, height, rand()%10+5),SColor(255, rand()%255, rand()%255, rand()%255));
                         break;}
                         case TELEPORT:{
                                   int id = 0, partner = 0;
                                   do{
                                        if(core::stringw("property") == xml->getNodeName()){
                                             if     (core::stringw("Id") == xml->getAttributeValue(L"name")){
                                                  id = xml->getAttributeValueAsInt(L"value");
                                             }
                                             else if(core::stringw("Partner") == xml->getAttributeValue(L"name")){
                                                  partner = xml->getAttributeValueAsInt(L"value");
                                             }
                                        }
                                        xml->read();
                                   }while(core::stringw("object") != xml->getNodeName());
                                   PhysicWorld::Instance()->GetTeletransportes()->push_back(PhysicWorld::Instance()->CreateTeleport(new Teleport(id, partner, irr::core::vector3df(x+(width/2)-100,-1*(y-(height/2)),0)))->Get());
                         break;}
                         case MUELLE:{
                                   int fuerza = 80;
                                   do{
                                        if(core::stringw("property") == xml->getNodeName()){
                                             if     (core::stringw("Fuerza") == xml->getAttributeValue(L"name")){
                                                  fuerza = xml->getAttributeValueAsFloat(L"value");
                                             }
                                        }
                                        xml->read();
                                   }while(core::stringw("object") != xml->getNodeName());
                                   PhysicWorld::Instance()->GetMuelles()->push_back(PhysicWorld::Instance()->CreateMuelle(new Muelle(fuerza,  irr::core::vector3df(x+(width/2)-100,-1*(y-(height/2)),0)))->Get());
                         break;}
                         case ARMA:{
                              int tipo, modelo;
                              do{
                                   if(core::stringw("property") == xml->getNodeName()){
                                        if     (core::stringw("Tipo") == xml->getAttributeValue(L"name")){
                                             tipo = xml->getAttributeValueAsFloat(L"value");
                                        }
                                        else if(core::stringw("Modelo") == xml->getAttributeValue(L"name")){
                                             modelo = xml->getAttributeValueAsFloat(L"value");
                                        }
                                   }
                                   xml->read();
                              }while(core::stringw("object") != xml->getNodeName());
                              switch(tipo){
                                   case PISTOLA:{
                                        PhysicWorld::Instance()->GetCogibles()->push_back(PhysicWorld::Instance()->CreatePistola(new Pistola(modelo,b2Vec2(x+(width/2)-100,-1*(y-(height/2)))))->Get());
                                   break;}
                                   case ESCOPETA:{
                                        PhysicWorld::Instance()->GetCogibles()->push_back(PhysicWorld::Instance()->CreateEscopeta(new Escopeta(modelo,irr::core::vector3df(x+(width/2)-100,-1*(y-(height/2)),0)))->Get());
                                   break;}
                                   case GRANADA:{
                                        PhysicWorld::Instance()->GetCogibles()->push_back(PhysicWorld::Instance()->CreateGranada(new Granada(modelo,irr::core::vector3df(x+(width/2)-100,-1*(y-(height/2)),0)))->Get());
                                   break;}
                              }
                    break;}
                    }
               }
          }
     }
}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Map::~Map(){}
