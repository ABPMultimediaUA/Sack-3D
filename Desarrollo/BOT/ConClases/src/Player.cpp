#include "Player.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

Player::Player(vector3df pos){
    vel = 20;
    cogiendo = false;
    puedoCoger = false;
    salto = false;
    dobleSaltando = false;
    fingiendoMuerte = false;
    jointDef = NULL;
    direccion = 1;
    tam = vector3df(8, 16,4);
    node = IrrManager::Instance()->addCubeSceneNode(tam,SColor(255, 255, 124, 150));
    node->setPosition(pos);

    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;

    bodyDef.position.Set(pos.X,pos.Y);
    bodyDef.type = b2_dynamicBody;

    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    body->SetFixedRotation(true);
    polyShape.SetAsBox(tam.X/2,tam.Y/2);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0;
    fixtureDef.restitution  = 0.3f;
    fixtureDef.density  = 10.f;
    body->CreateFixture(&fixtureDef);

    polyShape.SetAsBox(tam.X/4,tam.Y/4,b2Vec2(0,-tam.Y/2), 0);
    fixtureDef.isSensor = true;
    b2Fixture* personajeSensorFixture = body->CreateFixture(&fixtureDef);
    personajeSensorFixture->SetUserData((void*)100);

    eventReceiver = IrrManager::Instance()->getEventReciever();
}

void Player::update(){
    mover();
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()* 180 / 3.14159265));
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
    if(!fingiendoMuerte){
        if(!saltando){
            b2Vec2 velV = body->GetLinearVelocity();
            velV.y = vel;
            body->SetLinearVelocity(velV);
        }
        else if(!dobleSaltando){
            b2Vec2 velV = body->GetLinearVelocity();
            velV.y += vel/2;
            body->SetLinearVelocity(velV);
            dobleSaltando = true;
        }
    }
}
void Player::fingirMuerte(){
    if(!fingiendoMuerte){
        b2FixtureDef fixtureDef;
        b2CircleShape circleShape1;

        fingiendoMuerte = true;
        body->DestroyFixture(body->GetFixtureList());
        body->DestroyFixture(body->GetFixtureList());
        body->SetFixedRotation(false);
        circleShape1.m_p.Set(0,0);
        circleShape1.m_radius = 2;
        fixtureDef.shape = &circleShape1;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution  = 0.5f;
        fixtureDef.density  = 5.f;
        personFixture = body->CreateFixture(&fixtureDef);
        personFixture->SetUserData((void*)100);
        body->ApplyAngularImpulse(direccion);

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

        polyShape.SetAsBox(4,4);
        fixtureDef.isSensor = true;
        b2Fixture* personajeSensorFixture = body->CreateFixture(&fixtureDef);
        personajeSensorFixture->SetUserData((void*)100);
    }
}
void Player::crearJoint(b2Body* a, b2Body* b){
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = a;
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

void Player::romperJoint(){
    PhysicWorld::Instance()->GetWorld()->DestroyJoint(joint);
    joint = NULL;
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x +=20;
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
void  Player::setDobleSaltando(bool aux){dobleSaltando = aux;}
bool  Player::getCogiendo(){return cogiendo;}
int Player::getDireccion(){return direccion;}
void  Player::setCogiendo(bool aux){cogiendo = aux;}
bool  Player::getPuedoCoger(){return puedoCoger;}
void  Player::setPuedoCoger(bool aux){puedoCoger = aux;}
Player::~Player(){}
