
#include "Platform.h"
#include "World.h"

Platform::Platform(bool mata, b2Vec2 pos, irr::core::vector3df tam,irr::video::SColor color)
:GameObject(pos,tam,color){
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    bodyDef.position.Set(pos.x+(m_tam.X/2),-1*(pos.y-(m_tam.Y/2)));
    polyShape.SetAsBox((m_tam.X/2),(m_tam.Y/2));
    fixtureDef.shape = &polyShape;
    fixtureDef.filter.categoryBits = M_SUELO;
    if(mata)fixtureDef.isSensor = true;
    m_pBody  = m_pWorld->GetWorld()->CreateBody(&bodyDef);
    b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
    if(mata){
        fixture->SetUserData((void*)DATA_PINCHO);
        m_pNode->setVisible(false);
    }
}
//Platform::~Platform(){}
