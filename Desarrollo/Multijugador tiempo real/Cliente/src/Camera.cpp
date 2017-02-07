
#include "Camera.h"
#include "PhysicWorld.h"
#include "Player.h"

#define FPS 60 			

Camera::Camera(){
	camera = IrrManager::Instance()->getManager()->addCameraSceneNode(0, irr::core::vector3df(0,0,-140), irr::core::vector3df(0,0,0));
    timer = IrrManager::Instance()->getTimer();
    tiempoTransc = timer->getTime();
    cenAnt = new irr::core::vector3df(0,0,0);
    cenSig = new irr::core::vector3df(0,0,0);
    porcentGap = 0.2f;
    porcentUpdate = 0.0f;
    flowCam = new std::vector<irr::core::vector3df>();
    updateT = 1000.f/60.f;
    for(int i = 0; i<0 ;i++){
        flowCam->push_back(irr::core::vector3df(0,0,0));
    }
}
Camera::update(float time){
	float xP,yP,xB,yB,z;
	xP = PhysicWorld::Instance()->getPlayer(1)->getPosition().X;
	yP = PhysicWorld::Instance()->getPlayer(1)->getPosition().Y;
    xB = PhysicWorld::Instance()->getPlayer(2)->getPosition().X;
	yB = PhysicWorld::Instance()->getPlayer(2)->getPosition().Y;

	if(time - tiempoTransc > updateT){
    	tiempoTransc = timer->getTime();
        porcentUpdate = 0;
        cenAnt = new irr::core::vector3df(cenSig->X,cenSig->Y,0);
        cenSig = new irr::core::vector3df((xP + xB)/2,(yP + yB)/2,0);
        porcentGap = ceil(((1000.f/FPS)/updateT)*10)/10;
        updateT = 1000.f/(FPS/10.0f);
	}
	float cenX = cenAnt->X + ((cenSig->X - cenAnt->X)/(porcentGap*100)*porcentUpdate*10);
    float cenY = cenAnt->Y + ((cenSig->Y - cenAnt->Y)/(porcentGap*100)*porcentUpdate*10);
	z =  30;
	//if(z<35)z = 35;
    camera->setPosition(irr::core::vector3df(xP,yP, -z));
	//camera->setPosition(irr::core::vector3df(cenX,cenY, -z));
    camera->setTarget(irr::core::vector3df(xP,yP, 0));
	//camera->setTarget(irr::core::vector3df(cenX,cenY, 0));
    porcentUpdate += porcentGap;

}
Camera::setPosition(irr::core::vector3df pos){camera->setPosition(pos);}
Camera::setTarget(irr::core::vector3df pos){camera->setTarget(pos);}

