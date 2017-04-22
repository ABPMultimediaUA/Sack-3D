#include "PhysicBody/PBGranadaReleased.h"
#include "World.h"

PBGranadaReleased::PBGranadaReleased(){
    m_pWorld = World::Inst()->GetWorld();
    m_pBody = NULL;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBGranadaReleased::~PBGranadaReleased(){
	DestroyBody();
}
int PBGranadaReleased::Inicialize( b2Vec2 pos, b2Vec2 tam){
	DestroyBody();
	InitBody(pos,tam);
    SetFixedRotation(false);
    InitFixtures(tam);
    return m_bodyId;
}
b2Vec2 PBGranadaReleased::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBGranadaReleased::GetLinearVelocity(){
	return PhysicBody::DefGetLinearVelocity();
}
float    PBGranadaReleased::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBGranadaReleased::GetId(){
    return PhysicBody::DefGetId();
}
void   PBGranadaReleased::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBGranadaReleased::SetGravity(float gr){
    PhysicBody::DefSetGravity(gr);
}
void   PBGranadaReleased::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBGranadaReleased::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBGranadaReleased::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBGranadaReleased::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBGranadaReleased::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBGranadaReleased::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBGranadaReleased::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
void PBGranadaReleased::Catch(int id){
    PhysicBody::DefCatch(id);
}
void PBGranadaReleased::Release(){
    PhysicBody::DefRelease();
}
void PBGranadaReleased::DestroyFixtures(){
	for (b2Fixture* f = m_pBody->GetFixtureList(); f;){
        b2Fixture* fixtureToDestroy = f;
        f = f->GetNext();
        m_pBody->DestroyFixture( fixtureToDestroy );
    }
}
void PBGranadaReleased::DestroyBody(){
    if(m_pWorld && m_pBody){
       DestroyFixtures();
        m_pWorld->DestroyBody(m_pBody);
        m_pBody = NULL;
	}
}
void PBGranadaReleased::InitBody(b2Vec2 pos,b2Vec2 tam){
	b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x+(tam.x),-1*(pos.y-(tam.y)));
    bodyDef.type = b2_dynamicBody;
    m_pBody = m_pWorld->CreateBody(&bodyDef);
    m_bodyId = PhysicBody::GenerateId();
    m_pBody->SetUserData((void*)m_bodyId);
}
void PBGranadaReleased::InitFixtures(b2Vec2 tam){
	b2FixtureDef fixtureDef;
    b2CircleShape circleShape;
    b2PolygonShape polyShape;
    circleShape.m_p.Set(0,0);
    circleShape.m_radius = tam.x;
    fixtureDef.shape = &circleShape;
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
