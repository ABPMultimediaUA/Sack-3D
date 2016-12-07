#include "Player.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

Player::Player(vector3df pos){

    vel = 1000;
    cogiendo = false;
    puedoCoger = false;
    direccion = 1;
    salto = false;
    dobleSalto = false;
    fingiendoMuerte = false;
    jointDef = NULL;

    mesh = IrrManager::Instance()->getManager()->addCubeSceneNode(4);
    mesh->setPosition(vector3df(0,0,0));

    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;

    bodyDef.position.Set(0,0);
    bodyDef.type = b2_dynamicBody;

    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    body->SetFixedRotation(true);
    polyShape.SetAsBox(2,2);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution  = 0.3f;
    fixtureDef.density  = 100.0f;
    body->CreateFixture(&fixtureDef);

    polyShape.SetAsBox(4,4);
    fixtureDef.isSensor = true;
    b2Fixture* personajeSensorFixture = body->CreateFixture(&fixtureDef);
    personajeSensorFixture->SetUserData((void*)100);
}

void Player::update(){
    mesh->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    mesh->setRotation(vector3df(0,0,body->GetAngle()* 180 / 3.14159265));
}

void Player::mover(){
    if(!fingiendoMuerte){
        int dir = 0;
        if(eventReceiver->IsKeyDown(KEY_KEY_A))dir = -1;
        else if(eventReceiver->IsKeyDown(KEY_KEY_D))dir = 1;
        body->SetLinearVelocity(b2Vec2 (dir*vel, body->GetLinearVelocity().y));
    }
}

void Player::saltar(){
    b2Vec2 velV = body->GetLinearVelocity();
    if(!fingiendoMuerte){velV.y = vel;}else{velV.y = 10;}
    body->SetLinearVelocity(velV);
}

void Player::fingirMuerte(){
    if(!fingiendoMuerte){

        b2FixtureDef fixtureDef;
        b2CircleShape circleShape1;

        fingiendoMuerte = true;
        body->DestroyFixture(body->GetFixtureList());
        body->DestroyFixture(body->GetFixtureList());
        body->SetFixedRotation(true);
        circleShape1.m_p.Set(0,0);
        circleShape1.m_radius = 2;
        fixtureDef.shape = &circleShape1;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution  = 0.5f;
        fixtureDef.density  = 5.f;
        personFixture = body->CreateFixture(&fixtureDef);
        personFixture->SetUserData((void*)100);
        body->ApplyAngularImpulse(direccion);

        mesh->remove();
        mesh = IrrManager::Instance()->getManager()->addSphereSceneNode(2);

        if(cogiendo)this->soltar();

    }else{
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape polyShape;

        fingiendoMuerte = false;
        polyShape.SetAsBox(2,2);
        fixtureDef.shape = &polyShape;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution  = 0.3f;
        fixtureDef.density  = 100.0f;
        body->CreateFixture(&fixtureDef);
        body->SetFixedRotation(true);

        polyShape.SetAsBox(4,4);
        fixtureDef.isSensor = true;
        b2Fixture* personajeSensorFixture = body->CreateFixture(&fixtureDef);
        personajeSensorFixture->SetUserData((void*)100);

        mesh->remove();
        mesh = IrrManager::Instance()->getManager()->addCubeSceneNode(4);
    }
}

void Player::coger(b2Body* b){
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = this->body;
    jointDef.bodyB = b;
    //jointDef.collideConnected = false;
    //jointDef.localAnchorB = bodyPersonaje->GetLocalCenter();
    jointDef.localAnchorA.Set(0,0);
    jointDef.localAnchorB.Set(0,0);
    joint = (b2RevoluteJoint*)PhysicWorld::Instance()->GetWorld()->CreateJoint(&jointDef);
    joint->EnableMotor(true);
    joint->SetMaxMotorTorque(50.3f);
    cogiendo = true;

}

void Player::soltar(){
    PhysicWorld::Instance()->GetWorld()->DestroyJoint(joint);
    joint = NULL;
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x +=20*direccion;
    vel.y +=20;
    vel.x *=100;
    vel.y *=100;
    PhysicWorld::Instance()->getArma()->getBody()->ApplyLinearImpulse( vel, PhysicWorld::Instance()->getArma()->getBody()->GetLocalCenter());
    cogiendo = false;
}


b2Body* Player::getBody(){return body;}
vector3df Player::getPosition(){return vector3df(body->GetPosition().x,body->GetPosition().y,0);}
bool  Player::getSaltando(){return saltando;}
void  Player::setSaltando(bool aux){saltando = aux;}
void  Player::setDobleSaltando(bool aux){dobleSalto = aux;}
bool  Player::getDobleSaltando(){return dobleSalto;}
bool  Player::getCogiendo(){return cogiendo;}
int Player::getDireccion(){return direccion;}
void  Player::setCogiendo(bool aux){cogiendo = aux;}
bool  Player::getPuedoCoger(){return puedoCoger;}
void  Player::setPuedoCoger(bool aux){puedoCoger = aux;}

Player::~Player(){}
