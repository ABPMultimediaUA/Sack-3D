#include "Cogible.h"

Cogible::Cogible(){}
Cogible::~Cogible(){}
void Cogible::DestroyFixtures(){
	for (b2Fixture* f = body->GetFixtureList(); f;){
	    b2Fixture* fixtureToDestroy = f;
	    f = f->GetNext();
	    body->DestroyFixture( fixtureToDestroy );
	}
}
void Cogible::InicializeFixtures(int mode){
	b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.X/2.0f,tam.Y/2.0f);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = friction;
    fixtureDef.restitution  = restitution;
    fixtureDef.density  = density;
    if(mode == RELEASE){
        b2Fixture* fixture = body->CreateFixture(&fixtureDef);
        fixture->SetUserData((void*)ARMA);
        polyShape.SetAsBox((tam.X*2.0f),(tam.Y*2.0f));
    }
    fixtureDef.isSensor = true;
    b2Fixture* sensorFixture = body->CreateFixture(&fixtureDef);
    sensorFixture->SetUserData((void*)SENSOR);
}
void Cogible::actualiza(){
    if(cogido)node->setPosition(irr::core::vector3df(body->GetPosition().x+((5.0f/MPP)*dir),body->GetPosition().y,0));
    else node->setPosition(irr::core::vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(irr::core::vector3df(0,0,body->GetAngle()*RADTOGRAD));
}
void Cogible::setDireccion(int d){if(d != 0) dir = d;}
void Cogible::setCogido(bool aux){
	DestroyFixtures();
    if(aux) InicializeFixtures(CATCH);
    else InicializeFixtures(RELEASE);
    cogido = aux;
}
bool Cogible::getCogido(){return cogido;}
b2Body* Cogible::getBody(){return body;}
