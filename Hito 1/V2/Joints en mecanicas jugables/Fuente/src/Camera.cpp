/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Camera.h

Author:        Estudio Rorschach
Created:       26/11/2016 Jorge Puerto
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que contiene el codigo de funcionamiento para la camara.
*******************************************************************************/

#include "Camera.h"
#include "Player.h"
#include "Bot.h"

#define FPS 60 			///<


/******************************************************************************
                               Camera
*******************************************************************************
//---------------------------------------------------------------------------
/**
   Constructor
*/
Camera::Camera(){
	physicWorld = PhysicWorld::Instance();
	camera = IrrManager::Instance()->getManager()->addCameraSceneNode(0, vector3df(0,0,-140), vector3df(0,0,0));
    timer = IrrManager::Instance()->getTimer();
    tiempoTransc = timer->getTime();
    cenAnt = new vector3df(0,0,0);
    cenSig = new vector3df(0,0,0);
    porcentGap = 0.2f;
    porcentUpdate = 0.0f;
    flowCam = new std::vector<vector3df>();
    updateT = 1000.f/60.f;
    for(int i = 0; i<0 ;i++){
        flowCam->push_back(vector3df(0,0,0));
    }
}
//---------------------------------------------------------------------------
/**
   Actualizar
*/
Camera::update(float time){
	float xP,yP,xB,yB,z;
	xP = physicWorld->getPlayer()->getPosition().X;
	yP = physicWorld->getPlayer()->getPosition().Y;
	xB = physicWorld->getBot()->getPosition().X;
	yB = physicWorld->getBot()->getPosition().Y;
	if(time - tiempoTransc > updateT){
    	tiempoTransc = timer->getTime();
        porcentUpdate = 0;
        cenAnt = new vector3df(cenSig->X,cenSig->Y,0);
        cenSig = new vector3df((xP + xB)/2,(yP + yB)/2,0);
        porcentGap = ceil(((1000.f/FPS)/updateT)*10)/10;
        updateT = 1000.f/(FPS/10.0f);
	}
	float cenX = cenAnt->X + ((cenSig->X - cenAnt->X)/(porcentGap*100)*porcentUpdate*10);
    float cenY = cenAnt->Y + ((cenSig->Y - cenAnt->Y)/(porcentGap*100)*porcentUpdate*10);
	z =  ((abs((xP - xB)*100)/100.f)+( (abs((yP - yB)*100)/100.f)*16.f/9.f))/2.f;
	if(z<35)z = 35;
	camera->setPosition(vector3df(cenX,cenY, -z));
	camera->setTarget(vector3df(cenX,cenY, 0));
    porcentUpdate += porcentGap;

}
//---------------------------------------------------------------------------
/**
   Getters y setters
*/
Camera::setPosition(vector3df pos){camera->setPosition(pos);}
Camera::setTarget(vector3df pos){camera->setTarget(pos);}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Camera::~Camera(){}
