#ifndef CAMERA_H
#define CAMERA_H

#include "IrrManager.h"
#include <Box2D/Box2D.h>
#include <vector>

class GameCamera{
    public:
        GameCamera();
        virtual ~GameCamera();
        update(float time,int fps);
    private:
        
    	irr::scene::ICameraSceneNode* camera;
        irr::ITimer* timer;
        float tiempoTransc;
        float updateT;
        double porcentUpdate;
        double porcentGap;
        std::vector<irr::core::vector3df> flowCam;
        irr::core::matrix4 projMat;
        b2Vec2 cenAnt;
        b2Vec2 cenSig;
        int fpsAnt;
};
#endif