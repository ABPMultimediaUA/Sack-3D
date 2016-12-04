#include "Camera.h"
#include "PhysicWorld.h"
#include "Player.h"
#include "Bot.h"
Camera::Camera(){
	camera = IrrManager::Instance()->getManager()->addCameraSceneNode(0, vector3df(0,0,-140), vector3df(0,0,0));
}
Camera::update(){
	float xP,yP,xB,yB,x,y,z;
	xP = PhysicWorld::Instance()->getPlayer()->getPosition().X;
	yP = PhysicWorld::Instance()->getPlayer()->getPosition().Y;
	xB = PhysicWorld::Instance()->getBot()->getPosition().X;
	yB = PhysicWorld::Instance()->getBot()->getPosition().Y;
	x = (xP + xB)/2;
	y = (yP + yB)/2;
	z =  abs(xP - xB)+( abs(yP - yB)*16/9);
	camera->setPosition(vector3df(x,y, -z));
	camera->setTarget(vector3df(x,y, 0));
}
Camera::setPosition(vector3df pos){camera->setPosition(pos);}
Camera::setTarget(vector3df pos){camera->setTarget(pos);}
Camera::~Camera(){}
