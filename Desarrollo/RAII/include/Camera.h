#ifndef CAMERA_H
#define CAMERA_H
#include "IrrManager.h"
#include <vector>
class Camera{
    public:
        Camera();
        virtual ~Camera(){}
        update(float time);
    private:
    	irr::scene::ICameraSceneNode* camera;
        irr::ITimer* timer;
        float tiempoTransc;
        float updateT;
        double porcentUpdate;
        double porcentGap;
        std::vector<irr::core::vector3df>* flowCam;
        irr::core::vector3df* cenAnt;
        irr::core::vector3df* cenSig;
};
#endif
