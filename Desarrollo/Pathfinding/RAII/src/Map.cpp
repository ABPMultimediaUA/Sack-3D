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

#include "Lista.h"
#include "Nodo.h"
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
     int mapw=0;
     int maph=0;

     int matriPath[10][10]{
        {0,0,0,0,0,0,0,0,0,0},  //nodo Inicial = (2,1)
        {0,0,0,8,0,0,0,0,0,0},  //nodo Final   = (2,5)
        {0,1,0,8,0,2,0,0,0,0},
        {0,0,0,8,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
     };

     Nodo *nodoIni;
     Nodo *nodoFin;
     b2Vec2 posicionI;
     b2Vec2 posicionF;
     b2Vec2 posicion;

     Lista *listaAbierta = new Lista();
     Lista *listaCerrada = new Lista();
     std::cout<<std::endl;
     //Nodo(b2Vec2 posicion, Nodo* nodoFinal, Nodo* nodoPadre, int g)
     for(int i = 0; i<10; i++){
        for(int j =0; j< 10; j++){
            if(matriPath[i][j]==1){
                posicionI.x = i;
                posicionI.y = j;
                std::cout<<"Nodo Inicial: "<<i<<" "<<j<<std::endl;
            }
            else if(matriPath[i][j]==2){
                posicionF.x = i;
                posicionF.y = j;
                std::cout<<"Nodo Final: "<<i<<" "<<j<<std::endl;
            }
        }
     }
     nodoIni = new Nodo (posicionI, nullptr, nullptr, 0);
     nodoFin = new Nodo (posicionF, nullptr, nullptr, 0);

     //Siguiendo este tutorial:   http://www.policyalmanac.org/games/articulo1.htm

     if(nodoIni->getDatos().x == nodoFin->getDatos().x && nodoIni->getDatos().y == nodoFin->getDatos().y){
          //Fin de algoritmo ya que inicio y fin son iguales
     }
     else{ //Comienza el Pathfinding
          listaAbierta->insertar(nodoIni); // Paso 2: Se adiciona el nodo inicial a la lista abierta
          //listaAbierta->insertar(nodoFin); // Paso 2: Se adiciona el nodo inicial a la lista abierta
          Nodo* nodoActual = nodoIni;
          posicion = posicionI;
          std::cout<<std::endl;

          if(listaAbierta->getHead() != nullptr){ //Paso 3: Mientras la lista abierta no esté vacía, se recorre cada nodo
              int i = posicion.x;
              int j = posicion.y;

              if(matriPath[i-1][j]!=8){
                  posicion.x = i-1;
                  posicion.y = j;
                  std::cout<<"Inserto en lista abierta: "<<i-1<<" "<<j<<std::endl;
                  listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );

              }if(matriPath[i+1][j]!=8){
                  posicion.x = i+1;
                  posicion.y = j;
                                    std::cout<<"Inserto en lista abierta: "<<i+1<<" "<<j<<std::endl;

                  listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );
              }if(matriPath[i][j-1]!=8){
                  posicion.x = i;
                  posicion.y = j-1;
                                    std::cout<<"Inserto en lista abierta: "<<i<<" "<<j-1<<std::endl;

                  listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );
              }if(matriPath[i][j+1]!=8){
                  posicion.x = i;
                  posicion.y = j+1;                  std::cout<<"Inserto en lista abierta: "<<i<<" "<<j+1<<std::endl;

                  listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );
              }if(matriPath[i-1][j-1]!=8){
                  posicion.x = i-1;
                  posicion.y = j-1;
                                    std::cout<<"Inserto en lista abierta: "<<i-1<<" "<<j-1<<std::endl;

                  listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 14) );
              }if(matriPath[i-1][j+1]!=8){
                  posicion.x = i-1;
                  posicion.y = j+1;
                                    std::cout<<"Inserto en lista abierta: "<<i-1<<" "<<j+1<<std::endl;

                  listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 14) );
              }if(matriPath[i+1][j+1]!=8){
                  posicion.x = i+1;
                  posicion.y = j+1;
                                    std::cout<<"Inserto en lista abierta: "<<i+1<<" "<<j+1<<std::endl;

                  listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 14) );
              }if(matriPath[i+1][j-1]!=8){
                  posicion.x = i+1;
                  posicion.y = j-1;                  std::cout<<"Inserto en lista abierta: "<<i+1<<" "<<j-1<<std::endl;

                  listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 14) );
              }

              listaAbierta->remove(nodoActual->posicion);
              nodoActual->setNext(nullptr);
              listaCerrada->insertar(nodoActual);

              //std::cout<<"Posciion nodo nuevo: "<<nodoActual->posicion.x<<" "<<nodoActual->posicion.y<<std::endl;

              if(listaAbierta->getTamanyo() > 0){
                nodoActual = listaAbierta->getMenorCosto();
                std::cout<<"Costo total nodo nuevo: "<<nodoActual->costoTotal<<std::endl;
              }

              //std::cout<<"Posciion nodo nuevo: "<<nodoActual->posicion.x<<" "<<nodoActual->posicion.y<<std::endl;
          }
        std::cout<<"///////////////////Soy Roberto y esto es Jackas//////////////////////"<<std::endl;
        bool estado = false;
        while( listaAbierta->getTamanyo() > 0 && listaAbierta->buscaNodo( nodoFin->getDatos().x, nodoFin->getDatos().y) == false) {
            std::cout<<std::endl;

            nodoActual = listaAbierta->getMenorCosto();
            std::cout<<"Costo total nodo nuevo: "<<nodoActual->costoTotal<<std::endl;
            listaAbierta->remove(nodoActual->posicion);
            nodoActual->setNext(nullptr);
            listaCerrada->insertar(nodoActual);

            std::cout<<"Tamanyo lista abierta: "<<listaAbierta->getTamanyo()<<std::endl;
            listaAbierta->imprimirLista(1);
            std::cout<<"Tamanyo lista cerrada: "<<listaCerrada->getTamanyo()<<std::endl;
            listaCerrada->imprimirLista(2);


            posicion = nodoActual->getDatos();
            int i = posicion.x;
            int j = posicion.y;

            std::cout<<"Posicion Actual: "<<i<<" "<<j<<std::endl;

            if(i-1>=0){
              if(matriPath[i-1][j]!=8 && listaCerrada->buscaNodo(i-1, j)==false ){
                  if(listaAbierta->buscaNodo(i-1, j)==false){
                      posicion.x = i-1;
                      posicion.y = j;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );
                  }
                  else{
                      //std::cout<<"G desde el primero: "<<listaAbierta->buscaNodo2(i-1, j)->getCostoDirecto()<<std::endl;
                      //std::cout<<"G desde el nuevo: "<<nodoActual->getCostoDirecto() + 10 <<std::endl;

                      if( (nodoActual->getCostoDirecto() + 10) < (listaAbierta->buscaNodo2(i-1, j)->getCostoDirecto()) ){
                          //cambia el padre del cuadro adyacente al cuadro seleccionado
                          //listaAbierta->buscaNodo2(i-1, j)->setPadre(nodoActual, 10);
                      }
                  }
              }
            }
            if(i+1<10){
              if(matriPath[i+1][j]!=8 && listaCerrada->buscaNodo(i+1, j)==false ){
                  if(listaAbierta->buscaNodo(i+1, j)==false){
                      posicion.x = i+1;
                      posicion.y = j;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );
                  }
                  else{
                      if( (nodoActual->getCostoDirecto() + 10) < (listaAbierta->buscaNodo2(i+1, j)->getCostoDirecto()) ){
                          //listaAbierta->buscaNodo2(i+1, j)->setPadre(nodoActual, 10);
                      }
                  }
              }
            }
            if(j-1>=0){
              if(matriPath[i][j-1]!=8 && listaCerrada->buscaNodo(i, j-1)==false ){
                  if(listaAbierta->buscaNodo(i, j-1)==false){
                      posicion.x = i;
                      posicion.y = j-1;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );
                  }
                  else{
                      if( (nodoActual->getCostoDirecto() + 10) < (listaAbierta->buscaNodo2(i, j-1)->getCostoDirecto()) ){
                          //listaAbierta->buscaNodo2(i, j-1)->setPadre(nodoActual, 10);
                      }
                  }
              }
            }
            if(j+1<10){
              if(matriPath[i][j+1]!=8 && listaCerrada->buscaNodo(i, j+1)==false ){
                  if(listaAbierta->buscaNodo(i, j+1)==false){
                      posicion.x = i;
                      posicion.y = j+1;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );
                  }
                  else{
                      if( (nodoActual->getCostoDirecto() + 10) < (listaAbierta->buscaNodo2(i, j+1)->getCostoDirecto()) ){
                          //listaAbierta->buscaNodo2(i, j+1)->setPadre(nodoActual, 10);
                      }
                  }
              }
            }
            if(i-1>=0 && j-1>=0){
              if(matriPath[i-1][j-1]!=8 && listaCerrada->buscaNodo(i-1, j-1)==false ){
                  if(listaAbierta->buscaNodo(i-1, j-1)==false){
                      posicion.x = i-1;
                      posicion.y = j-1;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 14) );
                  }
                  else{
                      if( (nodoActual->getCostoDirecto() + 14) < (listaAbierta->buscaNodo2(i-1, j-1)->getCostoDirecto()) ){
                         //listaAbierta->buscaNodo2(i-1, j-1)->setPadre(nodoActual, 14);
                      }
                  }
              }
            }
            if(i-1>=0 && j+1<10){
              if(matriPath[i-1][j+1]!=8 && listaCerrada->buscaNodo(i-1, j+1)==false ){
                  if(listaAbierta->buscaNodo(i-1, j+1)==false){
                      posicion.x = i-1;
                      posicion.y = j+1;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 14) );
                  }
                  else{
                      if( (nodoActual->getCostoDirecto() + 14) < (listaAbierta->buscaNodo2(i-1, j+1)->getCostoDirecto()) ){
                         //listaAbierta->buscaNodo2(i-1, j+1)->setPadre(nodoActual, 14);
                      }
                  }
              }
            }
            if(i+1<10 && j+1<10){
              if(matriPath[i+1][j+1]!=8 && listaCerrada->buscaNodo(i+1, j+1)==false ){
                  if(listaAbierta->buscaNodo(i+1, j+1)==false){
                      posicion.x = i+1;
                      posicion.y = j+1;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 14) );
                  }
                  else{
                      if( (nodoActual->getCostoDirecto() + 14) < (listaAbierta->buscaNodo2(i+1, j+1)->getCostoDirecto()) ){
                          //listaAbierta->buscaNodo2(i+1, j+1)->setPadre(nodoActual, 14);
                      }
                  }
              }
            }
            if(i+1<10 && j-1>=0){
              if(matriPath[i+1][j-1]!=8 && listaCerrada->buscaNodo(i+1, j-1)==false ){
                  if(listaAbierta->buscaNodo(i+1, j-1)==false){
                      posicion.x = i+1;
                      posicion.y = j-1;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 14) );
                  }
                  else{
                      if( (nodoActual->getCostoDirecto() + 14) < (listaAbierta->buscaNodo2(i+1, j-1)->getCostoDirecto()) ){
                          //listaAbierta->buscaNodo2(i+1, j-1)->setPadre(nodoActual, 14);
                      }
                  }
              }
            }
        std::cout<<"///////////////////////////////////////////////////////"<<std::endl;
        }//fin while pathfinding

        std::cout<<std::endl;
        std::cout<<"SALIDA PATHFINDING: "<<std::endl;

            //listaAbierta->imprimirLista(1);
            //listaCerrada->imprimirLista(2);
        /*nodoActual = listaAbierta->buscaNodo2(nodoFin->getDatos().x, nodoFin->getDatos().y);
        if(nodoActual!=nullptr){
            std::cout<<nodoActual->getDatos().x<<" "<<nodoActual->getDatos().y<<" : ";
            while (nodoActual->getDatos().x != nodoIni->getDatos().x && nodoActual->getDatos().y != nodoIni->getDatos().y){
              std::cout<<"cogeme si puedes"<<std::endl;
              nodoActual = nodoActual->getPadre();
              std::cout<<nodoActual->getDatos().x<<" "<<nodoActual->getDatos().y<<" : ";
            }
        }*/



     }











     while (xml->read()){
          //TAMANO DEL MAPA
         if(core::stringw("map") == xml->getNodeName()  && xml->getAttributeValue(L"width")){
            mapw = xml->getAttributeValueAsInt(L"width");
            maph = xml->getAttributeValueAsInt(L"height");
            int matriz[mapw][maph];
         }

        //MATRIZ PATHFINDING
        if(core::stringw("data") == xml->getNodeName()  && xml->getAttributeValue(L"encoding")){

            int matriz[mapw][maph];
            for(int i =0; i< maph; i++){
                for(int j=0; j<mapw; j++){
                    matriz[i][j]=0;
                }
            }
            char cadena[5000];
            char separador[] = ",";
            char *trozo = NULL;

            do{
                wcstombs(cadena, xml-> getNodeData(), 5000);

                int fila = 0; //maximo 36
                int columna = 0; //maximo 64

                trozo = strtok (cadena, separador);//separamos por coma y la recorremos
                //std::cout<<trozo<<std::endl;

                while(trozo!=nullptr && fila<36 && columna <64){

                    matriz[fila][columna] = atoi(trozo);
                    trozo = strtok( NULL, separador);

                    columna++;
                    if(columna == 64){
                        columna = 0;
                        fila++;
                    }

                   //trozo = strtok (cadena, separador);
                }

                xml->read();
               }while(core::stringw("data") != xml->getNodeName());

                //std::cout<<"Matriz: "<<matriz[4][5]<<std::endl;

          }





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
                                   Platform(vector3df(x+(width/2)-100,-1*(y+(height/2)),0),vector3df(width, height, rand()%10+5),SColor(255, rand()%255, rand()%255, rand()%255));
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
                                   PhysicWorld::Instance()->GetTeletransportes()->push_back(PhysicWorld::Instance()->CreateTeleport(new Teleport(id, partner, vector3df(x+(width/2)-100,-1*(y-(height/2)),0)))->Get());
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
                                   PhysicWorld::Instance()->GetMuelles()->push_back(PhysicWorld::Instance()->CreateMuelle(new Muelle(fuerza,  vector3df(x+(width/2)-100,-1*(y-(height/2)),0)))->Get());
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
                                        PhysicWorld::Instance()->GetCogibles()->push_back(PhysicWorld::Instance()->CreatePistola(new Pistola(modelo,vector3df(x+(width/2)-100,-1*(y-(height/2)),0)))->Get());
                                   break;}
                                   case ESCOPETA:{
                                        PhysicWorld::Instance()->GetCogibles()->push_back(PhysicWorld::Instance()->CreateEscopeta(new Escopeta(modelo,vector3df(x+(width/2)-100,-1*(y-(height/2)),0)))->Get());
                                   break;}
                                   case GRANADA:{
                                        PhysicWorld::Instance()->GetCogibles()->push_back(PhysicWorld::Instance()->CreateGranada(new Granada(modelo,vector3df(x+(width/2)-100,-1*(y-(height/2)),0)))->Get());
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
