#include "PhysicBody/PBCogibleCatched.h"
#include "World.h"

PBCogibleCatched::PBCogibleCatched(){
    m_pWorld = World::Inst()->GetWorld();
    m_pBody = NULL;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBCogibleCatched::~PBCogibleCatched(){
    DestroyBody();
}
int PBCogibleCatched::Inicialize( b2Vec2 pos, b2Vec2 tam){
	DestroyBody();
	InitBody(pos,tam);
    SetFixedRotation(true);
    InitFixtures(tam);
	SetAngularVelocity(0);
    SetRotation(0);
    m_pBody->SetGravityScale( 0 );
    m_pBody->SetLinearDamping(0);
    return m_bodyId;
}
b2Vec2 PBCogibleCatched::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBCogibleCatched::GetLinearVelocity(){
	return PhysicBody::DefGetLinearVelocity();
}

float    PBCogibleCatched::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBCogibleCatched::GetId(){
    return PhysicBody::DefGetId();
}
void   PBCogibleCatched::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBCogibleCatched::SetGravity(float gr){
    PhysicBody::DefSetGravity(gr);
}
void   PBCogibleCatched::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBCogibleCatched::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBCogibleCatched::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBCogibleCatched::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBCogibleCatched::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBCogibleCatched::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBCogibleCatched::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
void PBCogibleCatched::Catch(int id){
    PhysicBody::DefCatch(id);
}
void PBCogibleCatched::Release(){
    PhysicBody::DefRelease();
}
void PBCogibleCatched::DestroyFixtures(){
	for (b2Fixture* f = m_pBody->GetFixtureList(); f;){
        b2Fixture* fixtureToDestroy = f;
        f = f->GetNext();
        m_pBody->DestroyFixture( fixtureToDestroy );
    }
}
void PBCogibleCatched::DestroyBody(){
    if(m_pWorld && m_pBody){
       DestroyFixtures();
        m_pWorld->DestroyBody(m_pBody);
        m_pBody = NULL;
	}
}
void PBCogibleCatched::InitBody(b2Vec2 pos,b2Vec2 tam){
	b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x+(tam.x),-1*(pos.y-(tam.y)));
    bodyDef.type = b2_dynamicBody;
    m_pBody = m_pWorld->CreateBody(&bodyDef);
    m_bodyId = PhysicBody::GenerateId();
    m_pBody->SetUserData((void*)m_bodyId);
}
void PBCogibleCatched::InitFixtures(b2Vec2 tam){
	b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.x/2.0f,tam.y/2.0f);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0;
    fixtureDef.restitution  = 0;
    fixtureDef.density  =  0.0001f;
    fixtureDef.isSensor = true;
    m_pBody->CreateFixture(&fixtureDef);
    polyShape.SetAsBox(tam.x*4,tam.y*4);
    fixtureDef.shape = &polyShape;
    fixtureDef.filter.categoryBits = M_COGIBLESENSOR;
    fixtureDef.filter.maskBits = M_PLAYER;
    b2Fixture* sensorFixture = m_pBody->CreateFixture(&fixtureDef);
    sensorFixture->SetUserData((void*)DATA_COGIBLE_SENSOR);
}
