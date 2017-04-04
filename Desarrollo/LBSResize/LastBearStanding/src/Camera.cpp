
#include "Camera.h"
#include "World.h"
#include "Player.h"

#define MINZ            15
#define FPS             20
#define VIEWMARGIN      3

Camera::Camera(){
	camera = IrrMngr::Inst()->getManager()->addCameraSceneNode(0, irr::core::vector3df(0,0,-140), irr::core::vector3df(0,0,0));
    timer = IrrMngr::Inst()->getTimer();
    tiempoTransc = timer->getTime();
    cenAnt = b2Vec2(0,0);
    cenSig = b2Vec2(0,0);
    porcentGap = 0.2f;
    fpsAnt = 30;
    porcentUpdate = 0.0f;
    updateT = 1000.f/60.f;
    for(int i = 0; i<0 ;i++){
        flowCam.push_back(irr::core::vector3df(0,0,0));
    }
}
Camera::~Camera(){
    camera->remove();
}
Camera::update(float time, int fps){
	float xMin = 0,yMin = 0,xMax = 0,yMax = 0,z = 0;
    bool ini = false;
    for(unsigned int i = 0; i < World::Inst()->GetPlayers().size(); ++i){
        if(World::Inst()->GetPlayers().at(i)){
           if(!World::Inst()->GetPlayers().at(i)->getMuerto()){
                b2Vec2 pos = World::Inst()->GetPlayers().at(i)->getPosition();
                if(!ini){ xMin = xMax = pos.x; yMin = yMax = pos.y; ini = true;}
                if(pos.x < xMin)xMin = pos.x;
                if(pos.x > xMax)xMax = pos.x;
                if(pos.y < yMin)yMin = pos.y;
                if(pos.y > yMax)yMax = pos.y;
            }
        }
    }
	if(time - tiempoTransc > updateT || abs(fpsAnt - fps) >= 5){
    	tiempoTransc = timer->getTime();
        porcentUpdate = 0;
        cenAnt = b2Vec2(cenSig.x,cenSig.y);
        cenSig = b2Vec2((xMin + xMax)/2,(yMin + yMax)/2);
        porcentGap = ceil(((1000.f/fps)/updateT)*10)/10;
        updateT = 1000.f/(fps/10.0f);
        fpsAnt = fps;
	}
	float cenX = cenAnt.x + ((cenSig.x - cenAnt.x)/(porcentGap*100)*porcentUpdate*10);
    float cenY = cenAnt.y + ((cenSig.y - cenAnt.y)/(porcentGap*100)*porcentUpdate*10);
    z =  ((abs((xMin - xMax)*100)/100.f)+( (abs((yMin - yMax)*100)/200.f)*16.f/9.f));
	if(z<MINZ)z = MINZ;
    float incrementX = (float)abs(xMax-xMin);
    float incrementY = (float)abs(yMax-yMin);
    float tamX = incrementX+incrementY+VIEWMARGIN;
    float tamY = tamX*9/16;
    projMat.buildProjectionMatrixOrthoLH(tamX,tamY,-1000,1000);
    camera->setProjectionMatrix(projMat);
    flowCam.push_back(irr::core::vector3df(cenX,cenY,0));
    irr::core::vector3df aux = flowCam[0];
    flowCam.erase(flowCam.begin());
    camera->setPosition(irr::core::vector3df(aux.X,aux.Y, -z));
    camera->setTarget(irr::core::vector3df(aux.X,aux.Y, 0));

    porcentUpdate += porcentGap;

}

