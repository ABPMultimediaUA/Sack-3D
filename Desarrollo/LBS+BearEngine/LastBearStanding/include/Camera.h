#ifndef CAMERA_H
#define CAMERA_H

#include "BearManager.h"
#include <Box2D/Box2D.h>
#include <vector>

class GameCamera{
    public:
        GameCamera();
        ~GameCamera();
        glm::vec3 update(float time,int fps);
    private:
        uint32 tiempoTransc;
        float updateT;
        double porcentUpdate;
        double porcentGap;
        std::vector<glm::vec3> flowCam;
        //irr::core::matrix4 projMat;
        b2Vec2 cenAnt;
        b2Vec2 cenSig;
        float zAnt;
        float zSig;
        int fpsAnt;
};
#endif
