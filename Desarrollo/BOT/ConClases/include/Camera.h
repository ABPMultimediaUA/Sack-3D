#ifndef CAMERA_H
#define CAMERA_H
#include "IrrManager.h"


class Camera
{
    public:
        Camera();
        setPosition(vector3df pos);
        setTarget(vector3df pos); 
        virtual ~Camera();

    protected:

    private:
    	ICameraSceneNode* camera;
};

#endif // CAMERA_H
