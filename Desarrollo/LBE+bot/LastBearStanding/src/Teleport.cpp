#include "Teleport.h"
#include "World.h"
#include "IrrManager.h"

Teleport::Teleport(int i, int p, irr::core::vector3df pos, irr::core::vector3df tam ,irr::video::SColor color){
    id = i;
    partner = p;
    pos.X += (tam.X/2);
    pos.Y  = -1*(pos.Y-(tam.Y/2));
    node = IrrMngr::Inst()->addCubeSceneNode(irr::core::vector3df(tam.X, tam.Y,tam.Z),color);
    node->setPosition(irr::core::vector3df(pos.X, pos.Y, pos.Z));
    node->setMaterialTexture(0,IrrMngr::Inst()->getDriver()->getTexture("media/texture.jpg"));
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(pos.X,pos.Y);
    body  = World::Inst()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox((tam.X/2),(tam.Y/2));
    fixtureDef.shape = &polyShape;
    fixtureDef.filter.categoryBits = M_TELEPORT;
    fixtureDef.filter.maskBits = M_BALA|M_COGIBLE|M_PLAYER;
    b2Fixture* fixture = body->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)DATA_TELEPORT);
}
Teleport::~Teleport(){
}
int Teleport::getTeleportId(){return id;}
int Teleport::getTeleportPartnerId(){return partner;}
b2Body* Teleport::getBody(){return body;}

