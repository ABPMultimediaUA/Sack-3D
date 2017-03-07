#include "Teleport.h"
#include "World.h"

Teleport::Teleport(int id, int partner, b2Vec2 pos)
:GameObject(pos,irr::core::vector3df(0.5f, 3.f, 1.f),irr::video::SColor(0, 100, 100, 255)),m_id(id),m_partner(partner){
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(pos.x+(m_tam.X/2),-1*(pos.y-(m_tam.Y/2)));
    m_pBody  = m_pWorld->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox((m_tam.X/2),(m_tam.Y/2));
    fixtureDef.shape = &polyShape;
    fixtureDef.filter.categoryBits = M_TELEPORT;
    fixtureDef.filter.maskBits = M_BALA|M_COGIBLE|M_PLAYER;
    b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)DATA_TELEPORT);
}
Teleport::~Teleport(){}
int Teleport::getTeleportId(){return m_id;}
int Teleport::getTeleportPartnerId(){return m_partner;}

