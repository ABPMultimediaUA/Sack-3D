#include "Platform.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

Platform::Platform(vector3df pos, vector3df tam,SColor color){
    mesh = IrrManager::Instance()->createCubeMesh(vector3df(pos.X, pos.Y, pos.Z),vector3df(tam.X, tam.Y,tam.Z),color);
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.X,pos.Y);
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.X/2,tam.Y/2);
    body->CreateFixture(&polyShape, 0.0f);
}
Platform::~Platform(){}

