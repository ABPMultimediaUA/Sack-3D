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
#include "PhysicWorld.h"
#include "Player.h"
#include "Bot.h"

/******************************************************************************
                               Camera
*******************************************************************************
//---------------------------------------------------------------------------
/**
   Constructor
*/
Camera::Camera(){
	camera = IrrManager::Instance()->getManager()->addCameraSceneNode(0, vector3df(0,0,-140), vector3df(0,0,0));
}
//---------------------------------------------------------------------------
/**
   Actualizar
*/
Camera::update(){
	float xP,yP,xB,yB,x,y,z;
	xP = PhysicWorld::Instance()->getPlayer()->getPosition().X;
	yP = PhysicWorld::Instance()->getPlayer()->getPosition().Y;
	xB = PhysicWorld::Instance()->getBot()->getPosition().X;
	yB = PhysicWorld::Instance()->getBot()->getPosition().Y;
	x = (xP + xB)/2;
	y = (yP + yB)/2;
	z =  (abs(xP - xB)+( abs(yP - yB)*16/9))/2;
	camera->setPosition(vector3df(x,y, -z));
	camera->setTarget(vector3df(x,y, 0));
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
