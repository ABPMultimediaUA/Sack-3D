#include "PhysicWorld.h"
#include "MyContactListener.h"
PhysicWorld* PhysicWorld::pinstance = 0;
PhysicWorld* PhysicWorld::Instance(){
	if(pinstance == 0){
		pinstance = new PhysicWorld;
	}
	return pinstance;
}
PhysicWorld::PhysicWorld(){
	world = new b2World(b2Vec2(0.0f, -20.0f), true);
	cubos = new std::vector<cuboMierda*>();
	balas = new std::vector<Bala*>();
	myContactListenerInstance = new MyContactListener();
	world->SetContactListener(myContactListenerInstance);
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
std::vector<Bala*>* PhysicWorld::GetBalas(){return balas;}
void PhysicWorld::Step(float DeltaTime){ world->Step(DeltaTime*TIMESTEP, VELITER, POSITER);}
void PhysicWorld::ClearForces(){world->ClearForces();}
void PhysicWorld::setPlayer(Player* p){jugador1 = p;}
void PhysicWorld::setArma(Arma* a){arma = a;}
Player* PhysicWorld::getPlayer(){return jugador1;}
Arma* PhysicWorld::getArma(){return arma;}
PhysicWorld::~PhysicWorld(){}
