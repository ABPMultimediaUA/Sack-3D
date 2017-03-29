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
                }//fin while

                xml->read();
               }while(core::stringw("data") != xml->getNodeName());
        }

        if (xml->getNodeType() == irr::io::EXN_ELEMENT && core::stringw("object") == xml->getNodeName()){
            int x = xml->getAttributeValueAsInt(L"x");
            int y = xml->getAttributeValueAsInt(L"y");
            int width = xml->getAttributeValueAsInt(L"width");
            int height = xml->getAttributeValueAsInt(L"height");
            float rotation = xml->getAttributeValueAsInt(L"rotation");
            Platform(vector3df(x+(width/2),-1*(y+(height/2)),0),vector3df(width, height,  rand()%10+5), rotation ,SColor(255, rand()%255, rand()%255, rand()%255));
        }
    }

}

void Map::iniciarMatriz(int xI, int yI, int xF, int yF){
  
    yI = yI*-1;
    yF = yF*-1;


    matriz[yI/10][xI/10] = 1;
    matriz[yF/10][xF/10] = 2;
    
    posicionI.x = yI/10;
    posicionI.y = xI/10;
    posicionF.x = yF/10;
    posicionF.y = xF/10;
}

void Map::obtenerPathfinding(){
    Nodo *nodoIni;
    Nodo *nodoFin;
    b2Vec2 posicion;

    listaAbierta = new Lista();
    listaCerrada = new Lista();
    camino = new Lista();
    pathfinding = new Lista();
    std::cout<<std::endl;

    nodoIni = new Nodo (posicionI, nullptr, nullptr, 0);
    nodoFin = new Nodo (posicionF, nullptr, nullptr, 0);

    //Siguiendo este tutorial:   http://www.policyalmanac.org/games/articulo1.htm

    if(nodoIni->getDatos().x == nodoFin->getDatos().x && nodoIni->getDatos().y == nodoFin->getDatos().y){
        //Fin de algoritmo ya que inicio y fin son iguales
    }
    else{ //Comienza el Pathfinding
        listaAbierta->insertar(nodoIni); // Paso 2: Se adiciona el nodo inicial a la lista abierta
        //listaAbierta->insertar(nodoFin); // Paso 2: Se adiciona el nodo inicial a la lista abierta
        nodoActual = nodoIni;
        posicion = posicionI;
        std::cout<<std::endl;

        if(listaAbierta->getHead() != nullptr){ //Paso 3: Mientras la lista abierta no esté vacía, se recorre cada nodo
            int i = posicion.x;
            int j = posicion.y;

            if(i-1>=0)
              comprobar(i-1, j, 10,nodoActual, nodoFin);
            if(i+1<36)
              comprobar(i+1, j, 10,nodoActual, nodoFin);
            if(j-1>=0)
              comprobar(i, j-1, 10,nodoActual, nodoFin);
            if(j+1<64)
              comprobar(i, j+1, 10,nodoActual, nodoFin);
            if(i-1>=0 && j-1>=0)
              comprobar(i-1, j-1, 14,nodoActual, nodoFin);
            if(i-1>=0 && j+1<64)
              comprobar(i-1, j+1, 14,nodoActual, nodoFin);
            if(i+1<36 && j+1<64)
              comprobar(i+1, j+1, 14,nodoActual, nodoFin);
            if(i+1<36 && j-1>=0)
              comprobar(i+1, j-1, 14,nodoActual, nodoFin);

            listaAbierta->remove(nodoActual->posicion);
            nodoActual->setNext(nullptr);
            listaCerrada->insertar(nodoActual);

            if(listaAbierta->getTamanyo() > 0)
              nodoActual = listaAbierta->getMenorCosto();
        }

      while( listaAbierta->getTamanyo() > 0 && listaAbierta->buscaNodo( nodoFin->getDatos().x, nodoFin->getDatos().y) == false) {
          std::cout<<std::endl;

          nodoActual = listaAbierta->getMenorCosto();
          listaAbierta->remove(nodoActual->posicion);
          nodoActual->setNext(nullptr);
          listaCerrada->insertar(nodoActual);

          posicion = nodoActual->getDatos();
          int i = posicion.x;
          int j = posicion.y;
          std::cout<<"Posicion Actual: "<<i<<" "<<j<<std::endl;

          if(i-1>=0)
            comprobar(i-1, j, 10,nodoActual, nodoFin);

          if(i+1<36)
            comprobar(i+1, j, 10,nodoActual, nodoFin);

          if(j-1>=0)
            comprobar(i, j-1, 10,nodoActual, nodoFin);

          if(j+1<64)
            comprobar(i, j+1, 10,nodoActual, nodoFin);

          if(i-1>=0 && j-1>=0)
            comprobar(i-1, j-1, 14,nodoActual, nodoFin);

          if(i-1>=0 && j+1<64)
            comprobar(i-1, j+1, 14,nodoActual, nodoFin);

          if(i+1<36 && j+1<64)
            comprobar(i+1, j+1, 14,nodoActual, nodoFin);

          if(i+1<36 && j-1>=0)
            comprobar(i+1, j-1, 14,nodoActual, nodoFin);

      }//fin while pathfinding
      std::cout<<std::endl;

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
      matriz[(int)posicionI.x][(int)posicionI.y] = 0;
      matriz[(int)posicionF.x][(int)posicionF.y] = 0;

      //invertimos la lista para q el path vaya de inicio a fin
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
}//fin funcion

void Map::comprobar(int i, int j, int peso, Nodo* nodoActual, Nodo* nodoFin){
    b2Vec2 posicion;

    if(matriz[i][j]!=8 && listaCerrada->buscaNodo(i, j)==false){

        if(listaAbierta->buscaNodo(i, j) == false){
            posicion.x = i;
            posicion.y = j;
            listaAbierta->insertar( new Nodo (posicion, nodoFin, nodoActual, peso) );
        }
        else{
          if( (nodoActual->getCostoDirecto() + peso) < (listaAbierta->buscaNodo2(i, j)->getCostoDirecto()) )
              //cambiamos padre del cuadro adyacente al cuadro seleccionado
              listaAbierta->buscaNodo2(i, j)->setPadre(nodoActual, peso);
        }
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
