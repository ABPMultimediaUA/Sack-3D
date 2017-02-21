
#include "Camera.h"
#include "World.h"
#include "Player.h"
#include "PlayerRed.h"

#define FPS  60
#define MINZ 15

Camera::Camera(){
	camera = IrrMngr::Inst()->getManager()->addCameraSceneNode(0, irr::core::vector3df(0,0,-140), irr::core::vector3df(0,0,0));
    timer = IrrMngr::Inst()->getTimer();
    tiempoTransc = timer->getTime();
    cenAnt = b2Vec2(0,0);
    cenSig = b2Vec2(0,0);
    porcentGap = 0.2f;
    porcentUpdate = 0.0f;
    updateT = 1000.f/60.f;
    for(int i = 0; i<0 ;i++){
        flowCam.push_back(irr::core::vector3df(0,0,0));
    }
}
Camera::~Camera(){
    camera->remove();
}
Camera::update(float time){
	float xMin,yMin,xMax,yMax,z;
    bool ini = false;
    bool puedo = false;
    for(int i = 0; i <= World::Inst()->GetPlayersRed().size() || i==0; ++i){
        b2Vec2 pos;
        if(i==World::Inst()->GetPlayersRed().size()){
            if(!World::Inst()->GetPlayers().at(0)->getMuerto()){ pos = World::Inst()->GetPlayers().at(0)->getPosition();
            puedo = true;
            }
        }
        else {
            if(World::Inst()->GetPlayersRed().at(i)->getMuerto() == 0){ pos = World::Inst()->GetPlayersRed().at(i)->getPosition();
                puedo = true;
            }
        }
        if(puedo){
            if(!ini){ xMin = xMax = pos.x; yMin = yMax = pos.y; ini = true;}
            if(pos.x < xMin)xMin = pos.x;
            if(pos.x > xMax)xMax = pos.x;
            if(pos.y < yMin)yMin = pos.y;
            if(pos.y > yMax)yMax = pos.y;
        }
    }
    for(int i = 0; i < World::Inst()->GetPlayers().size(); ++i){
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
	if(time - tiempoTransc > updateT){
    	tiempoTransc = timer->getTime();
        porcentUpdate = 0;
        cenAnt = b2Vec2(cenSig.x,cenSig.y);
        cenSig = b2Vec2((xMin + xMax)/2,(yMin + yMax)/2);
        porcentGap = ceil(((1000.f/FPS)/updateT)*10)/10;
        updateT = 1000.f/(FPS/10.0f);
	}
	float cenX = cenAnt.x + ((cenSig.x - cenAnt.x)/(porcentGap*100)*porcentUpdate*10);
    float cenY = cenAnt.y + ((cenSig.y - cenAnt.y)/(porcentGap*100)*porcentUpdate*10);
    z =  ((abs((xMin - xMax)*100)/100.f)+( (abs((yMin - yMax)*100)/200.f)*16.f/9.f));
	if(z<MINZ)z = MINZ;
    flowCam.push_back(irr::core::vector3df(cenX,cenY,0));
    irr::core::vector3df aux = flowCam[0];
    flowCam.erase(flowCam.begin());
    camera->setPosition(irr::core::vector3df(aux.X,aux.Y, -z));
    camera->setTarget(irr::core::vector3df(aux.X,aux.Y, 0));
    porcentUpdate += porcentGap;

}

