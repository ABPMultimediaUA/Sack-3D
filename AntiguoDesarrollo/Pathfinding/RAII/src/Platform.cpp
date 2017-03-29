#include "Platform.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

Platform::Platform(irr::core::vector3df pos, irr::core::vector3df tam,irr::video::SColor color){
    node = IrrManager::Instance()->addCubeSceneNode(irr::core::vector3df(tam.X, tam.Y,tam.Z),color);
    node->setPosition(irr::core::vector3df(pos.X, pos.Y, pos.Z));
    node->setMaterialTexture(0,IrrManager::Instance()->getDriver()->getTexture("media/texture.jpg"));
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(pos.X,pos.Y);
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox((tam.X/2),(tam.Y/2));
    body->CreateFixture(&polyShape, 0.0f);
}

