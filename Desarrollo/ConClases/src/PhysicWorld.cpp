#include "PhysicWorld.h"


PhysicWorld* PhysicWorld::pinstance = 0;
PhysicWorld* PhysicWorld::Instance(){
	if(pinstance == 0){
		pinstance = new PhysicWorld;
	}
	return pinstance;
}
PhysicWorld::PhysicWorld(){
	world = new b2World(b2Vec2(0.0f, -10.0f));
	cubos = new std::vector<cuboMierda*>();
	//players = new std::vector<Player*>();
}
b2World* PhysicWorld::GetWorld(){return world;}
b2Body* PhysicWorld::CreateBox(int x , int y){
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(x,y);
    bodyDef.type = b2_dynamicBody;
    b2Body* body  = world->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox(16,16);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 10.f;
    body->CreateFixture(&fixtureDef);
    return body;
}
std::vector<cuboMierda*>* PhysicWorld::GetCubos(){return cubos;}
void PhysicWorld::Step(float DeltaTime){ world->Step(DeltaTime*TIMESTEP, VELITER, POSITER);}
void PhysicWorld::ClearForces(){world->ClearForces();}
PhysicWorld::~PhysicWorld(){}
