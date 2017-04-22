#include "PhysicBody/PBMetralla.h"
#include "World.h"

PBMetralla::PBMetralla(){
    m_pWorld = World::Inst()->GetWorld();
    m_pBody = NULL;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBMetralla::~PBMetralla(){
	DestroyBody();
}
int PBMetralla::Inicialize( b2Vec2 pos, b2Vec2 tam){
	DestroyBody();
	InitBody(pos,tam);
    InitFixtures(tam);
    return m_bodyId;
}
b2Vec2 PBMetralla::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBMetralla::GetLinearVelocity(){
	return PhysicBody::DefGetLinearVelocity();
}
float    PBMetralla::GetRotation(){
    return PhysicBody::DefGetRotation();
}
void   PBMetralla::SetGravity(float gr){
    PhysicBody::DefSetGravity(gr);
}
int    PBMetralla::GetId(){
    return PhysicBody::DefGetId();
}
void   PBMetralla::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBMetralla::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBMetralla::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBMetralla::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBMetralla::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBMetralla::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBMetralla::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBMetralla::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
void PBMetralla::Catch(int id){
    PhysicBody::DefCatch(id);
}
void PBMetralla::Release(){
    PhysicBody::DefRelease();
}
void PBMetralla::DestroyFixtures(){
    for (b2Fixture* f = m_pBody->GetFixtureList(); f;){
        b2Fixture* fixtureToDestroy = f;
        f = f->GetNext();
        m_pBody->DestroyFixture( fixtureToDestroy );
    }
}
void PBMetralla::DestroyBody(){
    if(m_pWorld && m_pBody){
       DestroyFixtures();
       m_pWorld->DestroyBody(m_pBody);
       m_pBody = NULL;
    }
}
void PBMetralla::InitBody(b2Vec2 pos,b2Vec2 tam){
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x+(tam.x),-1*(pos.y-(tam.y)));
    bodyDef.type = b2_dynamicBody;
    m_pBody = m_pWorld->CreateBody(&bodyDef);
    m_bodyId = PhysicBody::GenerateId();
    m_pBody->SetUserData((void*)m_bodyId);
}
void PBMetralla::InitFixtures(b2Vec2 tam){
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.x/2.0f,tam.y/2.0f);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0.1f;
    fixtureDef.restitution  = .99f;
    fixtureDef.density  =  2.0f;
    fixtureDef.filter.categoryBits = M_BALA;
    fixtureDef.filter.maskBits = M_SUELO|M_PLAYER;
    b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)DATA_METRALLA);
}
