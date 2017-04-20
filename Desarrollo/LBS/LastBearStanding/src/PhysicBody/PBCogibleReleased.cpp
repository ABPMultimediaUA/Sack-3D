#include "PhysicBody/PBCogibleReleased.h"
#include "World.h"

PBCogibleReleased::PBCogibleReleased(){
    m_pWorld = World::Inst()->GetWorld();
    m_pBody = NULL;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBCogibleReleased::~PBCogibleReleased(){
	DestroyBody();
}
int PBCogibleReleased::Inicialize( b2Vec2 pos, b2Vec2 tam){
	DestroyBody();
	InitBody(pos,tam);
    SetFixedRotation(false);
    InitFixtures(tam);
    return m_bodyId;
}
b2Vec2 PBCogibleReleased::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBCogibleReleased::GetLinearVelocity(){
	return PhysicBody::DefGetLinearVelocity();
}
float    PBCogibleReleased::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBCogibleReleased::GetId(){
    return PhysicBody::DefGetId();
}
void   PBCogibleReleased::SetGravity(float gr){
    PhysicBody::DefSetGravity(gr);
}
void   PBCogibleReleased::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBCogibleReleased::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBCogibleReleased::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBCogibleReleased::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBCogibleReleased::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBCogibleReleased::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBCogibleReleased::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBCogibleReleased::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
void PBCogibleReleased::Catch(int id){
    PhysicBody::DefCatch(id);
}
void PBCogibleReleased::Release(){
    PhysicBody::DefRelease();
}
void PBCogibleReleased::DestroyFixtures(){
	for (b2Fixture* f = m_pBody->GetFixtureList(); f;){
        b2Fixture* fixtureToDestroy = f;
        f = f->GetNext();
        m_pBody->DestroyFixture( fixtureToDestroy );
    }
}
void PBCogibleReleased::DestroyBody(){
    if(m_pWorld && m_pBody){
       DestroyFixtures();
        m_pWorld->DestroyBody(m_pBody);
        m_pBody = NULL;
	}
}
void PBCogibleReleased::InitBody(b2Vec2 pos,b2Vec2 tam){
	b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x+(tam.x),-1*(pos.y-(tam.y)));
    bodyDef.type = b2_dynamicBody;
    m_pBody = m_pWorld->CreateBody(&bodyDef);
    m_bodyId = PhysicBody::GenerateId();
    m_pBody->SetUserData((void*)m_bodyId);
}
void PBCogibleReleased::InitFixtures(b2Vec2 tam){
	b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.x/2.0f,tam.y/2.0f);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0.8f;
    fixtureDef.restitution  = 0.2f;
    fixtureDef.density  =  2.0f;
    fixtureDef.filter.categoryBits = M_COGIBLE;
    fixtureDef.filter.maskBits = M_SUELO|M_COGIBLE|M_TELEPORT|M_MUELLE;
    b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)DATA_COGIBLE);
    fixtureDef.isSensor = true;
    polyShape.SetAsBox(tam.x*4,tam.y*4);
    fixtureDef.shape = &polyShape;
    fixtureDef.filter.categoryBits = M_COGIBLESENSOR;
    fixtureDef.filter.maskBits = M_PLAYER;
    b2Fixture* sensorFixture = m_pBody->CreateFixture(&fixtureDef);
    sensorFixture->SetUserData((void*)DATA_COGIBLE_SENSOR);
}
