#include "PhysicBody/PBDefaultSensor.h"
#include "World.h"

PBDefaultSensor::PBDefaultSensor(){
    m_pWorld = World::Inst()->GetWorld();
    m_pBody = NULL;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBDefaultSensor::~PBDefaultSensor(){
	DestroyBody();
}
int PBDefaultSensor::Inicialize( b2Vec2 pos, b2Vec2 tam){
	DestroyBody();
	InitBody(pos,tam);
    InitFixtures(tam);
    return m_bodyId;
}
b2Vec2 PBDefaultSensor::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBDefaultSensor::GetLinearVelocity(){
	return PhysicBody::DefGetLinearVelocity();
}
float    PBDefaultSensor::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBDefaultSensor::GetId(){
    return PhysicBody::DefGetId();
}
void   PBDefaultSensor::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBDefaultSensor::SetGravity(float gr){
    PhysicBody::DefSetGravity(gr);
}
void   PBDefaultSensor::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBDefaultSensor::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBDefaultSensor::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBDefaultSensor::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBDefaultSensor::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBDefaultSensor::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBDefaultSensor::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
void PBDefaultSensor::Catch(int id){
    PhysicBody::DefCatch(id);
}
void PBDefaultSensor::Release(){
    PhysicBody::DefRelease();
}
void PBDefaultSensor::DestroyFixtures(){
    for (b2Fixture* f = m_pBody->GetFixtureList(); f;){
        b2Fixture* fixtureToDestroy = f;
        f = f->GetNext();
        m_pBody->DestroyFixture( fixtureToDestroy );
    }
}
void PBDefaultSensor::DestroyBody(){
    if(m_pWorld && m_pBody){
       DestroyFixtures();
        m_pWorld->DestroyBody(m_pBody);
        m_pBody = NULL;
    }
}
void PBDefaultSensor::InitBody(b2Vec2 pos,b2Vec2 tam){
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x+(tam.x),-1*(pos.y-(tam.y)));
    m_pBody = m_pWorld->CreateBody(&bodyDef);
    m_bodyId = PhysicBody::GenerateId();
    m_pBody->SetUserData((void*)m_bodyId);
}
void PBDefaultSensor::InitFixtures(b2Vec2 tam){
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.x,tam.y);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0.8f;
    fixtureDef.restitution  = 0.2f;
    fixtureDef.density  =  2.0f;
    fixtureDef.filter.categoryBits = m_category;
    fixtureDef.filter.maskBits = m_mask;
    fixtureDef.isSensor = true;
    b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)m_userData);
}
