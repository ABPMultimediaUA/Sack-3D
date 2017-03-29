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

#define RADTOGRAD 180 / 3.14159265  ///< Conversor de radianes a grados

/******************************************************************************
                               Bot
*******************************************************************************/


//---------------------------------------------------------------------------
/**
   Constructor
*/
Bot::Bot(vector3df pos):Player(pos){
    InicializarFuzzy();
}


double Bot::GetPeligro(){

}

double Bot::getDistancia(b2Body* a, b2Body* b){
}
//---------------------------------------------------------------------------

void Bot::InicializarFuzzy(){
}

/**
   Actualizar
*/
void Bot::update(){
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()*RADTOGRAD));
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
