#include "PhysicBody/PBDefault.h"
#include "World.h"

PBDefault::PBDefault(){
    m_pWorld = World::Inst()->GetWorld();
    m_pBody = NULL;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBDefault::~PBDefault(){
	DestroyBody();
}
int PBDefault::Inicialize( b2Vec2 pos, b2Vec2 tam){
	DestroyBody();
	InitBody(pos,tam);
    InitFixtures(tam);
    return m_bodyId;
}
b2Vec2 PBDefault::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBDefault::GetLinearVelocity(){
	return PhysicBody::DefGetLinearVelocity();
}
float    PBDefault::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBDefault::GetId(){
    return PhysicBody::DefGetId();
}
void   PBDefault::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBDefault::SetGravity(float gr){
    PhysicBody::DefSetGravity(gr);
}
void   PBDefault::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBDefault::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBDefault::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBDefault::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBDefault::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBDefault::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBDefault::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
void PBDefault::Catch(int id){
    PhysicBody::DefCatch(id);
}
void PBDefault::Release(){
    PhysicBody::DefRelease();
}
void PBDefault::DestroyFixtures(){
    for (b2Fixture* f = m_pBody->GetFixtureList(); f;){
        b2Fixture* fixtureToDestroy = f;
        f = f->GetNext();
        m_pBody->DestroyFixture( fixtureToDestroy );
    }
}
void PBDefault::DestroyBody(){
    if(m_pWorld && m_pBody){
       DestroyFixtures();
        m_pWorld->DestroyBody(m_pBody);
        m_pBody = NULL;
    }
}
void PBDefault::InitBody(b2Vec2 pos,b2Vec2 tam){
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x+(tam.x),-1*pos.y-(tam.y));
    m_pBody = m_pWorld->CreateBody(&bodyDef);
    m_bodyId = PhysicBody::GenerateId();
    m_pBody->SetUserData((void*)m_bodyId);
}
void PBDefault::InitFixtures(b2Vec2 tam){
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.x,tam.y);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 1;
    fixtureDef.restitution  = 0.f;
    fixtureDef.density  =  2.0f;
    fixtureDef.filter.categoryBits = m_category;
    fixtureDef.filter.maskBits = m_mask;
    b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)m_userData);
}
