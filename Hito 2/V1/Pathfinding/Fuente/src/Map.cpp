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
#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include "Platform.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/******************************************************************************
                               Map
*******************************************************************************
//---------------------------------------------------------------------------
/**
   Constructor
*/
Map::Map(stringw file){
    IXMLReader* xml = IrrManager::Instance()->createXMLReader(file);
    int mapw=64;
    int maph=36;

    while (xml->read()){

        //MATRIZ PATHFINDING
        if(core::stringw("data") == xml->getNodeName()  && xml->getAttributeValue(L"encoding")){

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
                //std::cout<<cadena<<std::endl;
                int fila = 0; //maximo 36
                int columna = 0; //maximo 64

                trozo = strtok (cadena, separador);//separamos por coma y la recorremos

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
        }



        if (xml->getNodeType() == irr::io::EXN_ELEMENT && core::stringw("object") == xml->getNodeName()){
            int x = xml->getAttributeValueAsInt(L"x");
            int y = xml->getAttributeValueAsInt(L"y");
            //x = x-60;
            //y = y-100;
            int width = xml->getAttributeValueAsInt(L"width");

            int height = xml->getAttributeValueAsInt(L"height");
            float rotation = xml->getAttributeValueAsInt(L"rotation");
            //Platform(vector3df(x+(width/2)-100,-1*(y+(height/2)),0),vector3df(width, height, rand()%10+5), rotation ,SColor(255, rand()%255, rand()%255, rand()%255));
            Platform(vector3df(x+(width/2),-1*(y+(height/2)),0),vector3df(width, height,  rand()%10+5), rotation ,SColor(255, rand()%255, rand()%255, rand()%255));
        }
    }

}

void Map::iniciarMatriz(int xI, int yI, int xF, int yF){

    yI = yI*-1;
    yF = yF*-1;

    std::cout<<"Que hay: "<<matriz[yF/10][xF/10]<<std::endl;

    matriz[yI/10][xI/10] = 1;
    matriz[yF/10][xF/10] = 2;
}

void Map::obtenerPathfinding(){
   Nodo *nodoIni;
   Nodo *nodoFin;
   b2Vec2 posicionI;
   b2Vec2 posicionF;
   b2Vec2 posicion;

   std::cout<<std::endl;

     Lista *listaAbierta = new Lista();
     Lista *listaCerrada = new Lista();
     Lista *camino = new Lista();
     pathfinding = new Lista();
     std::cout<<std::endl;

     //Nodo(b2Vec2 posicion, Nodo* nodoFinal, Nodo* nodoPadre, int g)
     for(int i = 0; i<36; i++){
        for(int j =0; j< 64; j++){
            if(matriz[i][j]==1){
                posicionI.x = i;
                posicionI.y = j;
                std::cout<<"Nodo Inicial: "<<i<<" "<<j<<std::endl;
            }
            else if(matriz[i][j]==2){
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

              if(matriz[i-1][j]!=8){
                  posicion.x = i-1;
                  posicion.y = j;
                  std::cout<<"Inserto en lista abierta: "<<i-1<<" "<<j<<std::endl;
                  listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );

              }if(matriz[i+1][j]!=8){
                  posicion.x = i+1;
                  posicion.y = j;
                                    std::cout<<"Inserto en lista abierta: "<<i+1<<" "<<j<<std::endl;

                  listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );
              }if(matriz[i][j-1]!=8){
                  posicion.x = i;
                  posicion.y = j-1;
                                    std::cout<<"Inserto en lista abierta: "<<i<<" "<<j-1<<std::endl;

                  listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );
              }if(matriz[i][j+1]!=8){
                  posicion.x = i;
                  posicion.y = j+1;                  std::cout<<"Inserto en lista abierta: "<<i<<" "<<j+1<<std::endl;

                  listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );
              }if(matriz[i-1][j-1]!=8 && matriz[i-1][j]!=8 && matriz[i][j-1]!=8){
                  posicion.x = i-1;
                  posicion.y = j-1;
                                    std::cout<<"Inserto en lista abierta: "<<i-1<<" "<<j-1<<std::endl;

                  listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 14) );
              }if(matriz[i-1][j+1]!=8 && matriz[i][j+1]!=8 && matriz[i-1][j]!=8){
                  posicion.x = i-1;
                  posicion.y = j+1;
                                    std::cout<<"Inserto en lista abierta: "<<i-1<<" "<<j+1<<std::endl;

                  listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 14) );
              }if(matriz[i+1][j+1]!=8 && matriz[i][j+1]!=8 && matriz[i+1][j]!=8){
                  posicion.x = i+1;
                  posicion.y = j+1;
                                    std::cout<<"Inserto en lista abierta: "<<i+1<<" "<<j+1<<std::endl;

                  listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 14) );
              }if(matriz[i+1][j-1]!=8 && matriz[i][j-1]!=8 && matriz[i+1][j]!=8){
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

        while( listaAbierta->getTamanyo() > 0 && listaAbierta->buscaNodo( nodoFin->getDatos().x, nodoFin->getDatos().y) == false) {
            std::cout<<std::endl;

            nodoActual = listaAbierta->getMenorCosto();
            std::cout<<"Costo total nodo nuevo: "<<nodoActual->costoTotal<<std::endl;
            listaAbierta->remove(nodoActual->posicion);
            nodoActual->setNext(nullptr);
            listaCerrada->insertar(nodoActual);

            std::cout<<"Tamanyo lista abierta: "<<listaAbierta->getTamanyo()<<std::endl;
            std::cout<<"Tamanyo lista cerrada: "<<listaCerrada->getTamanyo()<<std::endl;


            posicion = nodoActual->getDatos();
            int i = posicion.x;
            int j = posicion.y;

            std::cout<<"Posicion Actual: "<<i<<" "<<j<<std::endl;

            if(i-1>=0){
              if(matriz[i-1][j]!=8 && listaCerrada->buscaNodo(i-1, j)==false ){
                  if(listaAbierta->buscaNodo(i-1, j)==false){
                      posicion.x = i-1;
                      posicion.y = j;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );
                  }
                  else{


                      if( (nodoActual->getCostoDirecto() + 10) < (listaAbierta->buscaNodo2(i-1, j)->getCostoDirecto()) ){

                          //cambia el padre del cuadro adyacente al cuadro seleccionado
                          listaAbierta->buscaNodo2(i-1, j)->setPadre(nodoActual, 10);
                      }
                  }
              }
            }
            if(i+1<36){
              if(matriz[i+1][j]!=8 && listaCerrada->buscaNodo(i+1, j)==false ){
                  if(listaAbierta->buscaNodo(i+1, j)==false){
                      posicion.x = i+1;
                      posicion.y = j;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );
                  }
                  else{

                      if( (nodoActual->getCostoDirecto() + 10) < (listaAbierta->buscaNodo2(i+1, j)->getCostoDirecto()) ){
                          listaAbierta->buscaNodo2(i+1, j)->setPadre(nodoActual, 10);
                      }
                  }
              }
            }
            if(j-1>=0){
              if(matriz[i][j-1]!=8 && listaCerrada->buscaNodo(i, j-1)==false ){
                  if(listaAbierta->buscaNodo(i, j-1)==false){
                      posicion.x = i;
                      posicion.y = j-1;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );
                  }
                  else{

                      if( (nodoActual->getCostoDirecto() + 10) < (listaAbierta->buscaNodo2(i, j-1)->getCostoDirecto()) ){
                          listaAbierta->buscaNodo2(i, j-1)->setPadre(nodoActual, 10);
                      }
                  }
              }
            }
            if(j+1<64){
              if(matriz[i][j+1]!=8 && listaCerrada->buscaNodo(i, j+1)==false ){
                  if(listaAbierta->buscaNodo(i, j+1)==false){
                      posicion.x = i;
                      posicion.y = j+1;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 10) );
                  }
                  else{

                      if( (nodoActual->getCostoDirecto() + 10) < (listaAbierta->buscaNodo2(i, j+1)->getCostoDirecto()) ){

                          listaAbierta->buscaNodo2(i, j+1)->setPadre(nodoActual, 10);
                      }
                  }
              }
            }
            if(i-1>=0 && j-1>=0){
              if(matriz[i-1][j-1]!=8 && matriz[i][j-1]!=8 && matriz[i-1][j]!=8 && listaCerrada->buscaNodo(i-1, j-1)==false ){
                  if(listaAbierta->buscaNodo(i-1, j-1)==false){
                      posicion.x = i-1;
                      posicion.y = j-1;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 14) );
                  }
                  else{

                      if( (nodoActual->getCostoDirecto() + 14) < (listaAbierta->buscaNodo2(i-1, j-1)->getCostoDirecto()) ){
                          listaAbierta->buscaNodo2(i-1, j-1)->setPadre(nodoActual, 14);
                      }
                  }
              }
            }
            if(i-1>=0 && j+1<64){
              if(matriz[i-1][j+1]!=8 && matriz[i][j+1]!=8 && matriz[i-1][j]!=8 && listaCerrada->buscaNodo(i-1, j+1)==false ){
                  if(listaAbierta->buscaNodo(i-1, j+1)==false){
                      posicion.x = i-1;
                      posicion.y = j+1;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 14) );
                  }
                  else{

                      if( (nodoActual->getCostoDirecto() + 14) < (listaAbierta->buscaNodo2(i-1, j+1)->getCostoDirecto()) ){
                          listaAbierta->buscaNodo2(i-1, j+1)->setPadre(nodoActual, 14);
                      }
                  }
              }
            }
            if(i+1<36 && j+1<64){
              if(matriz[i+1][j+1]!=8 && matriz[i][j+1]!=8 && matriz[i+1][j]!=8 && listaCerrada->buscaNodo(i+1, j+1)==false ){
                  if(listaAbierta->buscaNodo(i+1, j+1)==false){
                      posicion.x = i+1;
                      posicion.y = j+1;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 14) );
                  }
                  else{

                      if( (nodoActual->getCostoDirecto() + 14) < (listaAbierta->buscaNodo2(i+1, j+1)->getCostoDirecto()) ){

                          listaAbierta->buscaNodo2(i+1, j+1)->setPadre(nodoActual, 14);
                      }
                  }
              }
            }
            if(i+1<36 && j-1>=0){
              if(matriz[i+1][j-1]!=8 && matriz[i][j-1]!=8 && matriz[i+1][j]!=8 && listaCerrada->buscaNodo(i+1, j-1)==false ){
                  if(listaAbierta->buscaNodo(i+1, j-1)==false){
                      posicion.x = i+1;
                      posicion.y = j-1;
                      listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, 14) );
                  }
                  else{

                      if( (nodoActual->getCostoDirecto() + 14) < (listaAbierta->buscaNodo2(i+1, j-1)->getCostoDirecto()) ){
                          listaAbierta->buscaNodo2(i+1, j-1)->setPadre(nodoActual, 14);
                      }
                  }
              }
            }
        std::cout<<"///////////////////////////////////////////////////////"<<std::endl;
        }//fin while pathfinding

        std::cout<<std::endl;
        std::cout<<"SALIDA PATHFINDING: "<<std::endl;

        nodoActual = listaAbierta->buscaNodo2(nodoFin->getDatos().x, nodoFin->getDatos().y);


        if(nodoActual){
            //imprimer el primer nodo
            camino->insertar(nodoActual);
            //std::cout<<nodoActual->getDatos().x<<" "<<nodoActual->getDatos().y<<" : ";
            while ( nodoActual->getDatos().x != nodoIni->getDatos().x || nodoActual->getDatos().y != nodoIni->getDatos().y ){

              nodoActual = nodoActual->getPadre();
              camino->insertar(nodoActual);
              //std::cout<<nodoActual->getDatos().x<<" "<<nodoActual->getDatos().y<<" : ";
            }
        }

        //Reiniciamos la matriz
        for(int x = 0; x< 36; x++){
          for(int y = 0; y<64; y++){
              if(matriz[x][y]==1)        matriz[x][y] = 0;
              else if(matriz[x][y]==2)   matriz[x][y] = 0;
          }
        }


        camino->imprimirLista();
        //invertimos la lista
        while(camino->getUltimo()){
            nodoActual = camino->getUltimo();
            pathfinding->insertar(nodoActual);
            camino->remove(nodoActual->posicion);
        }


        //pathfinding = invertirLista(*Lista camino);
        std::cout<<"<<<<<<<<<PATHFINDING>>>>>>>>>"<<std::endl;
        pathfinding->imprimirLista();

        std::cout<<std::endl;
     }

}

int Map::avanzarX(){
    Nodo *aux;
    aux = pathfinding->getHead();
  if(aux){
    return aux->getDatos().x;
  }
  return 0;
}
int Map::avanzarY(){
    Nodo *aux;
    aux = pathfinding->getHead();
    if(aux){
      pathfinding->remove(aux->getDatos());
      return aux->getDatos().y;
    }
    return 0;
}

//---------------------------------------------------------------------------
/**
   Destructor
*/
Map::~Map(){}
