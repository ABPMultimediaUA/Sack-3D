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
#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include "Platform.h"
#include <string.h>
#include <fstream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

/******************************************************************************
                               Map
*******************************************************************************
//---------------------------------------------------------------------------
/**
   Constructor
*/
Map::Map(stringw file){
    IXMLReader* xml = IrrManager::Instance()->createXMLReader(file);

    int matriz[57][89]; //patron de mapa en tiled filas*columnas 57x89 

    for(int i = 0; i< 57; i++){
      for(int j =0; j< 89; j++){
        matriz[i][j] = 0;
      }
    }

    cout<<"MAtriz creada"<<endl;

    while (xml->read()){

        if (xml->getNodeType() == irr::io::EXN_ELEMENT){

            if(core::stringw("object") == xml->getNodeName()){
                int x = xml->getAttributeValueAsInt(L"x");
                int y = xml->getAttributeValueAsInt(L"y");
                int width = xml->getAttributeValueAsInt(L"width");
                int height = xml->getAttributeValueAsInt(L"height");
                Platform(vector3df(x+(width/2)-100,-1*(y+(height/2)),0),vector3df(width, height, 10),SColor(255, rand()%255, rand()%255, rand()%255));
                //cout<<"gooooo"<<endl;
            }
            else if(core::stringw("data") == xml->getNodeName()){

                char cadena[512];
                char separador[] = ",";
                char *trozo = NULL;

                ifstream fe("media/matriz2.txt");

                for(int k =0; k<57; k++){
                  int i = 0;
                  fe.getline(cadena, 512); //cogemos primera fila
                  trozo = strtok (cadena, separador);//separamos por coma y la recorremos

                  while(trozo!=NULL){
                    if(k==44) 
                        cout<<"Trozo: "<<atoi(trozo)<<" "<<i<<endl; //esta fila tiene 8 ceros, luego 105 y para acabar 25 ceros

                    matriz[k][i] = atoi(trozo);
                    i++;
                    trozo = strtok( NULL, separador);
                  }
                  //cout << cadena << endl;
                }
            }
        }
    }// fin while
    //pintamos cualquier fila de la matriz completa 0-57
    for(int i = 7; i<9 ; i++){
      for(int j =0; j< 89; j++){
        cout<<matriz[i][j]<<" ";
      }
      cout<<endl;
    }

}


//---------------------------------------------------------------------------
/**
   Destructor
*/
Map::~Map(){}
