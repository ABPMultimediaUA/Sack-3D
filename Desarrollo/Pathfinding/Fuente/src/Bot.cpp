/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Bot.cpp

Author:        Estudio Rorschach
Created:
Modified:      08/12/2016 Jorge Puerto

Overview:

*******************************************************************************/
#include "Bot.h"
#include "PhysicWorld.h"

using namespace std;

#define CERCA 20
#define MEDIA CERCA*2
#define LEJOS CERCA*4
#define RADTOGRAD 180 / 3.14159265  ///< Conversor de radianes a grados

/******************************************************************************
                               Bot
*******************************************************************************/


//---------------------------------------------------------------------------
/**
   Constructor
*/
Bot::Bot(vector3df pos):Player(pos){
    //IrrManager::Instance()->getManager()->getMeshManipulator()->setVertexColors(mesh->getMesh(), SColor(255,255,0,0));
    distancia = 0;
}
//---------------------------------------------------------------------------
/**
   Actualizar
*/
void Bot::update(){

}
//---------------------------------------------------------------------------
/**

*/
int Bot::getMayorValor(int x1, int x2, int x3){
	if(x1>x2 && x1>x3){
		return 0;
	}
	else if(x2>x1 && x2>x3){
		return 1;
	}
	else
		return 2;
}
//---------------------------------------------------------------------------
/**

*/
int Bot::getMemership(float d){
	int x;
	x = 255-(4.25*(d-80));
	return abs(x);
}
//---------------------------------------------------------------------------
/**

*/
void Bot::huir(int dir){

}
//---------------------------------------------------------------------------
/**

*/
void Bot::quieto(){

}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Bot::~Bot(){}
