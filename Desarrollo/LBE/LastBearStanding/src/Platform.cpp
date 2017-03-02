
#include "Platform.h"
#include "World.h"
#include "IrrManager.h"

Platform::Platform(bool mata, irr::core::vector3df pos, irr::core::vector3df tam,irr::video::SColor color){
    node = NULL;
    if(!mata){
        node = IrrMngr::Inst()->addCubeSceneNode(irr::core::vector3df(tam.X, tam.Y,tam.Z),color);
        node->setPosition(irr::core::vector3df(pos.X+(tam.X/2), -1*(pos.Y+(tam.Y/2)), pos.Z));
        node->setMaterialTexture(0,IrrMngr::Inst()->getDriver()->getTexture("media/texture.jpg"));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox((tam.X/2),(tam.Y/2));
    fixtureDef.shape = &polyShape;
    fixtureDef.filter.categoryBits = M_SUELO;
    if(mata)fixtureDef.isSensor = true;
    bodyDef.position.Set(pos.X+(tam.X/2),-1*(pos.Y+(tam.Y/2)));
    body  = World::Inst()->GetWorld()->CreateBody(&bodyDef);
    b2Fixture* fixture = body->CreateFixture(&fixtureDef);
    if(mata)fixture->SetUserData((void*)DATA_PINCHO);
}
Platform::~Platform(){
    std::cout<<"BORRO PLATFORM"<<std::endl;
    if(node)node->remove();
    if(body)World::Inst()->GetWorld()->DestroyBody(body);
}
