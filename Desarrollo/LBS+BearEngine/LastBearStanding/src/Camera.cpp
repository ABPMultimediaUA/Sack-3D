
#include "Camera.h"
#include "World.h"
#include "Player.h"
#include "SDL.h"

#define MINZ            3
#define MAXZ            13
#define FPS             20
#define VIEWMARGIN      1

GameCamera::GameCamera(){
    tiempoTransc = SDL_GetTicks();
    cenAnt = b2Vec2(0,0);
    cenSig = b2Vec2(0,0);
    zAnt = 0;
    zSig = 0;
    porcentGap = 0.01f;
    fpsAnt = 30;
    porcentUpdate = 0.0f;
    updateT = 1000.f/60.f;
    for(int i = 0; i<0 ;i++){
        flowCam.push_back(glm::vec3(0,0,0));
    }
}
GameCamera::~GameCamera(){
}
glm::vec3 GameCamera::update(float time, int fps){
    int vivos = 0;
	float xMin = 0,yMin = 0,xMax = 0,yMax = 0,z = 0;
    bool ini = false;
    for(unsigned int i = 0; i < World::Inst()->GetPlayers().size(); ++i){
        if(World::Inst()->GetPlayers().at(i)){
           if(!World::Inst()->GetPlayers().at(i)->getMuerto()){
                vivos++;
                b2Vec2 pos = World::Inst()->GetPlayers().at(i)->getPosition();
                if(!ini){ xMin = xMax = pos.x; yMin = yMax = pos.y; ini = true;}
                if(pos.x < xMin)xMin = pos.x;
                if(pos.x > xMax)xMax = pos.x;
                if(pos.y < yMin)yMin = pos.y;
                if(pos.y > yMax)yMax = pos.y;
            }
        }
    }
    	if(vivos>0){
            if(SDL_GetTicks() - tiempoTransc > updateT || abs(fpsAnt - fps) >= 5){
                tiempoTransc = SDL_GetTicks();
                porcentUpdate = 0;
                cenAnt = b2Vec2(cenSig.x,cenSig.y);
                cenSig = b2Vec2((xMin + xMax)/2,(yMin + yMax)/2);
                zAnt = zSig;
                zSig =  ((abs((xMin - xMax)*100)/100.f)+( (abs((yMin - yMax)*100)/200.f)*16.f/9.f)*2)-1;
                porcentGap = ceil(((1000.f/fps)/updateT)*10)/10;
                updateT = 1000.f/(fps/10.0f);
                fpsAnt = fps;
            }
            float cenX = cenAnt.x + ((cenSig.x - cenAnt.x)/(porcentGap*100)*porcentUpdate*10);
            float cenY = cenAnt.y + ((cenSig.y - cenAnt.y)/(porcentGap*100)*porcentUpdate*10);
            z          = zAnt + ((zSig - zAnt)/(porcentGap*100)*porcentUpdate*10);;
            if(z<MINZ)z = MINZ;
            if(z>MAXZ)z = MAXZ;
            //std::cout<<z<<std::endl;
            float incrementX = (float)abs(xMax-xMin);
            float incrementY = (float)abs(yMax-yMin);
            float tamX = incrementX+(incrementY*2.2f)+VIEWMARGIN;
            if(tamX<3)tamX = 3;
            float tamY = tamX*9/16;
            //projMat.buildProjectionMatrixOrthoLH(tamX,tamY,-1000,1000);
            flowCam.push_back(glm::vec3(cenX,cenY,0));
            glm::vec3 aux = flowCam[0];
            flowCam.erase(flowCam.begin());
            BearMngr::Inst()->SetBearCameraPosition(aux.x,aux.y-(tamY/8.f), z);
            porcentUpdate += porcentGap;
            return glm::vec3(aux.x,aux.y-(tamY/8.f), z);
        }
}

