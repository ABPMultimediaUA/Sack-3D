#include "PhysicBody/PBSpawner.h"
#include "World.h"

PBSpawner::PBSpawner(){
    m_pWorld   = World::Inst()->GetWorld();
    m_pJoint   = NULL;
    m_pBody    = NULL;
    m_category = 0;
    m_userData = 0;
    m_mask     = 0;
}
PBSpawner::~PBSpawner(){
	DestroyBody();
}
int PBSpawner::Inicialize( b2Vec2 pos, b2Vec2 tam){
	DestroyBody();
	InitBody(pos,tam);
    SetFixedRotation(true);
    InitFixtures(tam);
    return m_bodyId;
}
b2Vec2 PBSpawner::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBSpawner::GetLinearVelocity(){
	return PhysicBody::DefGetLinearVelocity();
}
float    PBSpawner::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBSpawner::GetId(){
    return PhysicBody::DefGetId();
}
void   PBSpawner::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBSpawner::SetGravity(float gr){
    PhysicBody::DefSetGravity(gr);
}
void   PBSpawner::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBSpawner::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBSpawner::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBSpawner::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBSpawner::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBSpawner::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBSpawner::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
void PBSpawner::Catch(int id){
    b2RevoluteJointDef jointDef;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = 0;
    jointDef.bodyA = m_pBody;
    jointDef.bodyB = GetBodyWithId(id);
    jointDef.localAnchorA.Set(0,0.06f);
    jointDef.localAnchorB.Set(0,0);
    m_pJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&jointDef);
}
void PBSpawner::Release(){
    if(m_pJoint)
        m_pWorld->DestroyJoint(m_pJoint);
    m_pJoint = NULL;
}
void PBSpawner::DestroyFixtures(){
    for (b2Fixture* f = m_pBody->GetFixtureList(); f;){
        b2Fixture* fixtureToDestroy = f;
        f = f->GetNext();
        m_pBody->DestroyFixture( fixtureToDestroy );
    }
}
void PBSpawner::DestroyBody(){
    if(m_pWorld && m_pBody){
       DestroyFixtures();
        m_pWorld->DestroyBody(m_pBody);
        m_pBody = NULL;
    }
}
void PBSpawner::InitBody(b2Vec2 pos,b2Vec2 tam){
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x+(tam.x),-1*pos.y-(tam.y));
    m_pBody = m_pWorld->CreateBody(&bodyDef);
    m_bodyId = PhysicBody::GenerateId();
    m_pBody->SetUserData((void*)m_bodyId);
}
void PBSpawner::InitFixtures(b2Vec2 tam){
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.x/2.0f,tam.y/2.0f);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0.1f;
    fixtureDef.restitution  = 0.f;
    fixtureDef.density  =  2.0f;
    fixtureDef.filter.categoryBits = M_SPAWNER;
    fixtureDef.filter.maskBits = M_PLAYER|M_SUELO|M_COGIBLE|M_BALA|M_TELEPORT|M_MUELLE|M_COGIBLESENSOR|M_PINCHO|M_SPAWNER;
    b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)DATA_SPAWNER);
}
