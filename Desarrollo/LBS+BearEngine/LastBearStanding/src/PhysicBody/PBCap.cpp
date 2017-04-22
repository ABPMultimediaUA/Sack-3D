#include "PhysicBody/PBCap.h"
#include "World.h"

PBCap::PBCap(){
    m_pWorld = World::Inst()->GetWorld();
    m_pBody = NULL;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBCap::~PBCap(){
	DestroyBody();
}
int PBCap::Inicialize( b2Vec2 pos, b2Vec2 tam){
	DestroyBody();
	InitBody(pos,tam);
    InitFixtures(tam);
    return m_bodyId;
}
b2Vec2 PBCap::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBCap::GetLinearVelocity(){
	return PhysicBody::DefGetLinearVelocity();
}
float    PBCap::GetRotation(){
    return PhysicBody::DefGetRotation();
}

int    PBCap::GetId(){
    return PhysicBody::DefGetId();
}
void   PBCap::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBCap::SetGravity(float gr){
    PhysicBody::DefSetGravity(gr);
}
void   PBCap::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBCap::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBCap::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBCap::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBCap::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBCap::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBCap::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
void PBCap::Catch(int id){
    PhysicBody::DefCatch(id);
}
void PBCap::Release(){
    PhysicBody::DefRelease();
}
void PBCap::DestroyFixtures(){
    for (b2Fixture* f = m_pBody->GetFixtureList(); f;){
        b2Fixture* fixtureToDestroy = f;
        f = f->GetNext();
        m_pBody->DestroyFixture( fixtureToDestroy );
    }
}
void PBCap::DestroyBody(){
    if(m_pWorld && m_pBody){
       DestroyFixtures();
       m_pWorld->DestroyBody(m_pBody);
       m_pBody = NULL;
    }
}
void PBCap::InitBody(b2Vec2 pos,b2Vec2 tam){
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x+(tam.x),-1*(pos.y-(tam.y)));
    bodyDef.type = b2_dynamicBody;
    m_pBody = m_pWorld->CreateBody(&bodyDef);
    m_bodyId = PhysicBody::GenerateId();
    m_pBody->SetUserData((void*)m_bodyId);
}
void PBCap::InitFixtures(b2Vec2 tam){
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.x/2,tam.y/2);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction =       0.8f;
    fixtureDef.restitution  =   .7f;
    fixtureDef.density  =       1;
    fixtureDef.filter.categoryBits = M_PARTICULA;
    fixtureDef.filter.maskBits = M_PARTICULA|M_SUELO;
    b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)DATA_PARTICULA);
}
