#include "PhysicBody.h"
#include "PhysicWorld.h"

PhysicBody::PhysicBody(float posX,float posY,float tamX,float tamY){
	b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(posX,posY);
	bodyDef.type = b2_dynamicBody;
    b2Body* body = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tamX,tamY);
    fixtureDef.shape = &polyShape;
	fixtureDef.friction = 10.5f;
	fixtureDef.restitution  = 0.9f;
	fixtureDef.density  = 10.f;
    body->CreateFixture(&fixtureDef);
}
float PhysicBody::getX(){return body->GetPosition().x;}
float PhysicBody::getY(){return body->GetPosition().y;}
float PhysicBody::GetAngle(){return body->GetAngle()* 180 / 3.14159265;}
PhysicBody::~PhysicBody(){
}
