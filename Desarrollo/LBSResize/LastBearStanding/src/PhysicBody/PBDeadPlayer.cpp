#include "PhysicBody/PBDeadPlayer.h"
#include "World.h"

PBDeadPlayer::PBDeadPlayer(){
    m_pWorld = World::Inst()->GetWorld();
    m_pBody = NULL;
//    m_pJoint = NULL;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBDeadPlayer::~PBDeadPlayer(){
    DestroyBody();
}
int PBDeadPlayer::Inicialize( b2Vec2 pos, b2Vec2 tam){
	DestroyBody();
	InitBody(pos,tam);
    SetFixedRotation(false);
    InitFixtures(tam);
    b2Vec2 velocity = GetLinearVelocity();
    velocity.y += 5;
    SetLinearVelocity(velocity);
    return m_bodyId;
}
b2Vec2 PBDeadPlayer::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBDeadPlayer::GetLinearVelocity(){
	return PhysicBody::DefGetLinearVelocity();
}
float    PBDeadPlayer::GetRotation(){
    return PhysicBody::DefGetRotation();
}
void   PBDeadPlayer::SetGravity(float gr){
    PhysicBody::DefSetGravity(gr);
}
int    PBDeadPlayer::GetId(){
    return PhysicBody::DefGetId();
}
void   PBDeadPlayer::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBDeadPlayer::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBDeadPlayer::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBDeadPlayer::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBDeadPlayer::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBDeadPlayer::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBDeadPlayer::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBDeadPlayer::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
void PBDeadPlayer::Catch(int id){
    PhysicBody::DefCatch(id);
}
void PBDeadPlayer::Release(){
    PhysicBody::DefRelease();
}
void PBDeadPlayer::DestroyFixtures(){
	/*for (b2Fixture* f = m_pBody->GetFixtureList(); f;){
        b2Fixture* fixtureToDestroy = f;
        f = f->GetNext();
        if(fixtureToDestroy) m_pBody->DestroyFixture( fixtureToDestroy );
    }*/
}
void PBDeadPlayer::DestroyBody(){
    if(m_pWorld && m_pBody){
       DestroyFixtures();
        m_pWorld->DestroyBody(m_pBody);
        m_pBody = NULL;
	}
}
void PBDeadPlayer::InitBody(b2Vec2 pos,b2Vec2 tam){
	b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x+(tam.x),-1*(pos.y-(tam.y)));
    bodyDef.type = b2_dynamicBody;
    m_pBody = m_pWorld->CreateBody(&bodyDef);
    m_bodyId = PhysicBody::GenerateId();
    m_pBody->SetUserData((void*)m_bodyId);
}
void PBDeadPlayer::InitFixtures(b2Vec2 tam){
    float friction = .8f,
    	  restitution = 0.2f,
    	  density = 2;

	b2FixtureDef fixtureDef;
    b2CircleShape circleShape1;
    circleShape1.m_p.Set(0,-(tam.y/2.f));
    circleShape1.m_radius = (tam.y)/3.f;
    fixtureDef.shape = &circleShape1;
    fixtureDef.friction = friction;
    fixtureDef.restitution  = restitution;
    fixtureDef.density  = density;
    fixtureDef.filter.maskBits = M_SUELO;
    b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)DATA_PLAYER);

    b2FixtureDef fixtureDef2;
    b2CircleShape circleShape2;
    circleShape2.m_p.Set(0,(tam.y/2.f));
    circleShape2.m_radius = (tam.y)/3.f;
    fixtureDef2.shape = &circleShape2;
    fixtureDef2.friction = friction;
    fixtureDef2.restitution  =restitution;
    fixtureDef2.density  = density;
    fixtureDef.filter.maskBits = M_SUELO;
    b2Fixture* personFixture2 = m_pBody->CreateFixture(&fixtureDef2);
    personFixture2->SetUserData((void*)DATA_PLAYER);
}
