#include "cuboMierda.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

cuboMierda::cuboMierda(int x, int y){
    int tam = 8;
	node = IrrManager::Instance()->addCubeSceneNode(tam, SColor(255, rand()%255, rand()%255, rand()%255));
    node->setPosition(vector3df(x,y,0));
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(x,y);
    bodyDef.type = b2_dynamicBody;
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam/2,tam/2);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 10.f;
    body->CreateFixture(&fixtureDef);

    /*polyShape.SetAsBox(10,10);
    fixtureDef.isSensor = true;
    b2Fixture* cubomierdaSensorFixture = body->CreateFixture(&fixtureDef);
    cubomierdaSensorFixture->SetUserData((void*)30);*/
}
void cuboMierda::actualiza(){
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()* 180 / 3.14159265));
}

b2Body* cuboMierda::getBody(){
    return body;
}
cuboMierda::~cuboMierda(){}
