#include "Muelle.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

Muelle::Muelle(float f, irr::core::vector3df pos, irr::core::vector3df tam,irr::video::SColor color){
    fuerza = f;
    node = IrrManager::Instance()->addCubeSceneNode(irr::core::vector3df(tam.X, tam.Y,tam.Z),color);
    node->setPosition(irr::core::vector3df(pos.X, pos.Y-tam.Y/2, pos.Z));
    node->setMaterialTexture(0,IrrManager::Instance()->getDriver()->getTexture("media/texture.jpg"));
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(pos.X,pos.Y-tam.Y/2);
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox((tam.X/2),(tam.Y/2));

    b2Fixture* fixture = body->CreateFixture(&polyShape, 0.0f);
    fixture->SetUserData((void*)50);
}
float Muelle::getFuerza(){return fuerza;}
b2Body* Muelle::getBody(){return body;}
