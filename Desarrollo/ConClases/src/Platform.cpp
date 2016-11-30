#include "Platform.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

Platform::Platform(vector3df pos, vector3df tam,SColor color){
    mesh = IrrManager::Instance()->createCubeMesh(vector3df(pos.X, pos.Y, pos.Z),vector3df(tam.X, tam.Y,tam.Z),color);
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(pos.X,pos.Y);
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.X/2,tam.Y/2);
    body->CreateFixture(&polyShape, 0.0f);

   // polyShape.SetAsBox(tam.X/2,tam.Y/2);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution  = 0.0f;
    fixtureDef.density  = 0.0f;
    fixtureDef.isSensor = true;
    b2Fixture* plataformaSensorFixture = body->CreateFixture(&fixtureDef);
    plataformaSensorFixture->SetUserData((void*)20);
}
Platform::~Platform(){}

