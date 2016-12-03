#include "Camera.h"

Camera::Camera(){
	camera = IrrManager::Instance()->getManager()->addCameraSceneNode(0, vector3df(0,0,-140), vector3df(0,0,0));
}
Camera::setPosition(vector3df pos){camera->setPosition(pos);}
Camera::setTarget(vector3df pos){camera->setTarget(pos);}
Camera::~Camera(){}
