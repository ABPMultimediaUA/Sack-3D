#include "Muelle.h"
#include "World.h"
#include "IrrManager.h"

Muelle::Muelle(float f, b2Vec2 pos, irr::core::vector3df tam,irr::video::SColor color)
:GameObject(pos,tam,color){
    m_fuerza = f;
    b2PolygonShape polyShape;
    polyShape.SetAsBox((m_tam.X/2),(m_tam.Y/2));
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polyShape;
    fixtureDef.filter.categoryBits = M_MUELLE;
    fixtureDef.filter.maskBits = M_COGIBLE|M_PLAYER;
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x+(m_tam.X/2),-1*(pos.y-(m_tam.Y/2)));
    m_pBody  = m_pWorld->GetWorld()->CreateBody(&bodyDef);
    b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)DATA_MUELLE);
}
Muelle::~Muelle(){}
float Muelle::getFuerza(){return m_fuerza;}
