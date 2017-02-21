#include "Muelle.h"
#include "World.h"
#include "IrrManager.h"

Muelle::Muelle(float f, irr::core::vector3df pos, irr::core::vector3df tam,irr::video::SColor color){
    fuerza = f;
    pos.X += (tam.X/2);
    pos.Y  = -1*(pos.Y-(tam.Y/2));
    node = IrrMngr::Inst()->addCubeSceneNode(irr::core::vector3df(tam.X, tam.Y,tam.Z),color);
    node->setPosition(irr::core::vector3df(pos.X, pos.Y, pos.Z));
    node->setMaterialTexture(0,IrrMngr::Inst()->getDriver()->getTexture("media/texture.jpg"));
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);b2BodyDef bodyDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox((tam.X/2),(tam.Y/2));
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polyShape;
    fixtureDef.filter.categoryBits = M_MUELLE;
    fixtureDef.filter.maskBits = M_COGIBLE|M_PLAYER;
    bodyDef.position.Set(pos.X,pos.Y);
    body  = World::Inst()->GetWorld()->CreateBody(&bodyDef);

    b2Fixture* fixture = body->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)DATA_MUELLE);
}
Muelle::~Muelle(){
    if(node)node->remove();
    if(body)World::Inst()->GetWorld()->DestroyBody(body);
}
float Muelle::getFuerza(){return fuerza;}
b2Body* Muelle::getBody(){return body;}
