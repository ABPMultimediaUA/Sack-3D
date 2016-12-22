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
    //mover();
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()*RADTOGRAD));

    float x1 = PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().x;
    float x2 = PhysicWorld::Instance()->getBot()->getBody()->GetPosition().x;
    float y1 = PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().y;
    float y2 = PhysicWorld::Instance()->getBot()->getBody()->GetPosition().y;

    float x = pow( x2 - x1, 2);
    float y = pow( y2 - y1, 2);

    distancia = sqrt(x+y);

    //membresia

    if (distancia<=CERCA){
    	cerca = 255;
    	intermedio = 0;
    	lejos = 0;
    }
    if (distancia==MEDIA){
    	cerca = 0;
    	intermedio = 255;
    	lejos = 0;
    }
    if (distancia>=LEJOS){
    	cerca = 0;
    	intermedio = 0;
    	lejos = 255;
    }

    if(distancia<MEDIA && distancia>CERCA){
        //funciona
    	cerca = getMemership(distancia);
    	intermedio = 255-cerca;
    	lejos = 0;
    }
    if(distancia>MEDIA && distancia<LEJOS){
    	lejos = getMemership(distancia);
    	intermedio = 255-lejos;
    	cerca = 0;
    }




    switch(getMayorValor(cerca, intermedio, lejos)){
        case 0:
        	if(x2>x1){huir(1);}
        	else{huir(-1);}

        break;
        case 1: quieto();
        break;
        case 2: quieto();
        break;
        default: huir(1);
    }
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
	b2Vec2 velV = body->GetLinearVelocity();
    velV.x = vel*dir;
    body->SetLinearVelocity(velV);
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
