#include "PhysicBody/PBBullet.h"
#include "World.h"

PBBullet::PBBullet(){
    m_pWorld = World::Inst()->GetWorld();
    m_pBody = NULL;
    m_category = 0;
    m_userData = 0;
    m_mask = 0;
}
PBBullet::~PBBullet(){
	DestroyBody();
}
int PBBullet::Inicialize( b2Vec2 pos, b2Vec2 tam){
	DestroyBody();
	InitBody(pos,tam);
    InitFixtures(tam);
    return m_bodyId;
}
b2Vec2 PBBullet::GetPosition(){
	return PhysicBody::DefGetPosition();
}
b2Vec2 PBBullet::GetLinearVelocity(){
	return PhysicBody::DefGetLinearVelocity();
}
float    PBBullet::GetRotation(){
    return PhysicBody::DefGetRotation();
}
void   PBBullet::SetGravity(float gr){
    PhysicBody::DefSetGravity(gr);
}
int    PBBullet::GetId(){
    return PhysicBody::DefGetId();
}
void   PBBullet::SetRotation(float angle){
	PhysicBody::DefSetRotation(angle);
}
void   PBBullet::SetFixedRotation(bool fixed){
	PhysicBody::DefSetFixedRotation(fixed);
}
void   PBBullet::SetPosition(b2Vec2 pos){
	PhysicBody::DefSetPosition(pos);
}
void   PBBullet::SetAngularVelocity(float vel){
	PhysicBody::DefSetAngularVelocity(vel);
}
void   PBBullet::SetLinearVelocity(b2Vec2 vel){
	PhysicBody::DefSetLinearVelocity(vel);
}
void   PBBullet::SetCategory(uint16 i){
    PhysicBody::DefSetCategory(i);
}
void   PBBullet::SetUserData(int i){
    PhysicBody::DefSetUserData(i);
}
void   PBBullet::SetMask(uint16 i){
    PhysicBody::DefSetMask(i);
}
void PBBullet::Catch(int id){
    PhysicBody::DefCatch(id);
}
void PBBullet::Release(){
    PhysicBody::DefRelease();
}
void PBBullet::DestroyFixtures(){
    for (b2Fixture* f = m_pBody->GetFixtureList(); f;){
        b2Fixture* fixtureToDestroy = f;
        f = f->GetNext();
        m_pBody->DestroyFixture( fixtureToDestroy );
    }
}
void PBBullet::DestroyBody(){
    if(m_pWorld && m_pBody){
       DestroyFixtures();
       m_pWorld->DestroyBody(m_pBody);
       m_pBody = NULL;
    }
}
void PBBullet::InitBody(b2Vec2 pos,b2Vec2 tam){
    b2BodyDef bodyDef;
    bodyDef.bullet = true;
    bodyDef.position.Set(pos.x+(tam.x),-1*(pos.y-(tam.y)));
    bodyDef.type = b2_dynamicBody;
    m_pBody = m_pWorld->CreateBody(&bodyDef);
    m_bodyId = PhysicBody::GenerateId();
    m_pBody->SetUserData((void*)m_bodyId);
    m_pBody->SetGravityScale( 0 );
}
void PBBullet::InitFixtures(b2Vec2 tam){
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.x/2.0f,tam.y/2.0f);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0.1f;
    fixtureDef.restitution  = .99f;
    fixtureDef.density  =  2.0f;
    fixtureDef.filter.categoryBits = M_BALA;
    fixtureDef.filter.maskBits = M_SUELO|M_TELEPORT|M_PLAYER;
    b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)DATA_BALA);
}
