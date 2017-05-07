#include "PhysicBody/PBAlivePlayer.h"
#include "World.h"

PBAlivePlayer::PBAlivePlayer(){
    m_pWorld  = World::Inst()->GetWorld();
    m_pJoint  = NULL;
    m_pBody   = NULL;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBAlivePlayer::~PBAlivePlayer(){
    DestroyBody();
}
int PBAlivePlayer::Inicialize(b2Vec2 pos, b2Vec2 tam){
	DestroyBody();
	InitBody(pos, tam);
    SetFixedRotation(true);
    InitFixtures(tam);
    return m_bodyId;
}
b2Vec2 PBAlivePlayer::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBAlivePlayer::GetLinearVelocity(){
    return PhysicBody::DefGetLinearVelocity();
}
float    PBAlivePlayer::GetRotation(){
    return PhysicBody::DefGetRotation();
}
int    PBAlivePlayer::GetId(){
    return PhysicBody::DefGetId();
}
void   PBAlivePlayer::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBAlivePlayer::SetGravity(float gr){
    PhysicBody::DefSetGravity(gr);
}
void   PBAlivePlayer::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBAlivePlayer::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBAlivePlayer::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBAlivePlayer::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBAlivePlayer::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBAlivePlayer::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBAlivePlayer::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
void PBAlivePlayer::Catch(int id){
     b2RevoluteJointDef jointDef;
    jointDef.bodyA = m_pBody;
    jointDef.bodyB = GetBodyWithId(id);
    jointDef.localAnchorA.Set(0,0);
    jointDef.localAnchorB.Set(0,0);
    m_pJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&jointDef);
}
void PBAlivePlayer::Release(){
    if(m_pJoint)
        m_pWorld->DestroyJoint(m_pJoint);
    m_pJoint = NULL;
}
void PBAlivePlayer::DestroyFixtures(){
    for (b2Fixture* f = m_pBody->GetFixtureList(); f;){
        b2Fixture* fixtureToDestroy = f;
        f = f->GetNext();
        m_pBody->DestroyFixture( fixtureToDestroy );
    }
}
void PBAlivePlayer::DestroyBody(){
	if(m_pWorld && m_pBody){
        DestroyFixtures();
		m_pWorld->DestroyBody(m_pBody);
        m_pBody = NULL;
	}
}
void PBAlivePlayer::InitBody(b2Vec2 pos,b2Vec2 tam){
	b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x+(tam.x),-1*(pos.y-(tam.y)));
    bodyDef.type = b2_dynamicBody;
    m_pBody = m_pWorld->CreateBody(&bodyDef);
    m_bodyId = PhysicBody::GenerateId();
    m_pBody->SetUserData((void*)m_bodyId);
    m_pBody->SetLinearDamping(0);
}
void PBAlivePlayer::InitFixtures(b2Vec2 tam){
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox((tam.x),(tam.y));
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0;
    fixtureDef.restitution  = 0;
    fixtureDef.density  = 20;
    fixtureDef.filter.categoryBits = M_PLAYER;
    fixtureDef.filter.maskBits = M_BALA|M_NODO|M_SUELO|M_TELEPORT|M_MUELLE|M_COGIBLESENSOR;
    b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)DATA_PLAYER);
    polyShape.SetAsBox(tam.x/2,tam.y/2,b2Vec2(0,-tam.y), 0);
    fixtureDef.isSensor = true;
    fixtureDef.filter.maskBits = M_SUELO;
    b2Fixture* sensorFixture = m_pBody->CreateFixture(&fixtureDef);
    sensorFixture->SetUserData((void*)DATA_PLAYER_PIES);
}
