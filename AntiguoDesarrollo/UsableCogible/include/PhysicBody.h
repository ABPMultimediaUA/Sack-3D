#ifndef PHYSICBODY_H
#define PHYSICBODY_H

#include <Box2D/Box2D.h>
#include <iostream>

class PhysicBody{
    public:
        PhysicBody(float posX,float posY,float tamX,float tamY);
        float getX();
        float getY();
        float GetAngle();
        virtual ~PhysicBody();

    private:
    b2Body* body;
    float x;
    float y;
};

#endif // PHYSICBODY_H
