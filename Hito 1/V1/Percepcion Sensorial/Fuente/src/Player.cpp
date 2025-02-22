/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Player.cpp

Author:        Estudio Rorschach
Created:       11/11/2016 Jorge Puerto
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que define un player
*******************************************************************************/
#include "Player.h"
#include "PhysicWorld.h"
#include "IrrManager.h"
#include <math.h>

#define RADTOGRAD 180 / 3.14159265  ///< Conversor de radianes a grados
#define VELOCITATOR        10
#define DECELERATIX        50
#define MUY_LEJOS          50
#define LEJOS              40
#define DIST_MEDIA         30
#define CERCA              20
#define MUY_CERCA          10
#define MUY_RAPIDO         VELOCITATOR*5
#define RAPIDO             VELOCITATOR*4
#define VEL_MEDIA          VELOCITATOR*3
#define DESPACIO           VELOCITATOR*2
#define MUY_DESPACIO       VELOCITATOR
#define IZQUIERDA          1
#define DERECHA            2
#define NINGUNA            0

/******************************************************************************
                               Player
*******************************************************************************/
//---------------------------------------------------------------------------
/**
   Constructor
*/
Player::Player(vector3df pos){
    vel = 20;
    cont = 0;
    increment = 0.5f;
    cogiendo = false;
    puedoCoger = false;
    salto = 25;
    saltando = false;
    dobleSaltando = false;
    fingiendoMuerte = false;
    jointDef = NULL;
    direccion = 1;
    tam = vector3df(8, 8,8);
    //node = IrrManager::Instance()->addCubeSceneNode(tam, SColor(255, rand()%255, rand()%255, rand()%255));
    node = IrrManager::Instance()->addModel(tam, SColor(255, 255, 0, 0));
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
    fixtureDef.restitution  = 0;
    fixtureDef.density  =0.f;
    b2Fixture* fixture = body->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)10);
    polyShape.SetAsBox(tam.X/4,tam.Y/4,b2Vec2(0,-tam.Y/2), 0);
    fixtureDef.isSensor = true;
    b2Fixture* personajeSensorFixture = body->CreateFixture(&fixtureDef);
    personajeSensorFixture->SetUserData((void*)100);
    body->SetLinearVelocity(b2Vec2(1,1));
    eventReceiver = IrrManager::Instance()->getEventReciever();
    InitializeFuzzyModule();
}
//---------------------------------------------------------------------------
/**
   Actualiza posicion y rotacion
*/
void Player::update(){
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()* RADTOGRAD));
    b2PolygonShape* polygonShape = (b2PolygonShape*)body->GetFixtureList()->GetShape();


    //set up input
      b2RayCastInput input;
      b2RayCastInput input2;
      b2RayCastInput input3;
      b2Vec2 p1 = body->GetPosition();
      b2Vec2 p2 = b2Vec2(body->GetPosition().x+body->GetLinearVelocity().x*100,body->GetPosition().y+body->GetLinearVelocity().y*100);
      b2PolygonShape* polyShape = (b2PolygonShape*)body->GetFixtureList()->GetShape();
      b2Vec2 esquinaDcha = body->GetWorldPoint(b2Vec2(polyShape->GetVertex(3).x,polyShape->GetVertex(3).y));
      b2Vec2 vectDcha = b2Vec2(p1.x-esquinaDcha.x,p1.y-esquinaDcha.y);
      b2Vec2 esquinaIzq = body->GetWorldPoint(b2Vec2(polyShape->GetVertex(2).x,polyShape->GetVertex(2).y));
      b2Vec2 vectIzq = b2Vec2(p1.x-esquinaIzq.x,p1.y-esquinaIzq.y);
      vector3df izq = vector3df(p1.x+vectDcha.x*100,p1.y+vectDcha.y*100,0);
      vector3df dcha = vector3df(p1.x+vectIzq.x*100,p1.y+vectIzq.y*100,0);
      b2Vec2 p22 = b2Vec2(izq.X,izq.Y);
      b2Vec2 p23 = b2Vec2(dcha.X,dcha.Y);
      input.p1 = p1;
      input2.p1 = p1;
      input3.p1 = p1;
      input.p2 = p2;
      input2.p2 = p22;
      input3.p2 = p23;
      input.maxFraction = 1;
      input2.maxFraction = 1;
      input3.maxFraction = 1;

      //check every fixture of every body to find closest
      float closestFraction = 1; //start with end of line as p2
      float closestFraction2 = 1; //start with end of line as p2
      float closestFraction3 = 1; //start with end of line as p2
      b2Vec2 intersectionNormal(0,0);
      b2Vec2 intersectionNormal2(0,0);
      b2Vec2 intersectionNormal3(0,0);
      for (b2Body* b = PhysicWorld::Instance()->GetWorld()->GetBodyList(); b; b = b->GetNext()) {
          for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
              b2RayCastOutput output;
              if ( ! f->RayCast( &output, input,0 ) )
                  continue;
              if ( output.fraction < closestFraction ) {
                  closestFraction = output.fraction;
                  intersectionNormal = output.normal;
              }
          }
      }
    b2Vec2 intersectionPoint = p1 + closestFraction * (p2 - p1);
    for (b2Body* b = PhysicWorld::Instance()->GetWorld()->GetBodyList(); b; b = b->GetNext()) {
          for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
              b2RayCastOutput output;
              if ( ! f->RayCast( &output, input2,0 ) )
                  continue;
              if ( output.fraction < closestFraction2 ) {
                  closestFraction2 = output.fraction;
                  intersectionNormal2 = output.normal;
              }
          }
      }
    b2Vec2 intersectionPoint2 = p1 + closestFraction2 * (p22 - p1);
    for (b2Body* b = PhysicWorld::Instance()->GetWorld()->GetBodyList(); b; b = b->GetNext()) {
          for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
              b2RayCastOutput output;
              if ( ! f->RayCast( &output, input3,0 ) )
                  continue;
              if ( output.fraction < closestFraction3 ) {
                  closestFraction3 = output.fraction;
                  intersectionNormal3 = output.normal;
              }
          }
      }
    b2Vec2 intersectionPoint3 = p1 + closestFraction3 * (p23 - p1);
    int width = abs(intersectionPoint.x-p1.x);
    int height = abs(intersectionPoint.y-p1.y);
    float distance = sqrt(pow(width,2)+pow(height,2));
    if(distance>70)distance=70;
    int width2 = abs(intersectionPoint2.x-p1.x);
    int height2 = abs(intersectionPoint2.y-p1.y);
    float distance2 = sqrt(pow(width2,2)+pow(height2,2));

    int width3 = abs(intersectionPoint3.x-p1.x);
    int height3 = abs(intersectionPoint3.y-p1.y);
    float distance3 = sqrt(pow(width3,2)+pow(height3,2));


    IA(distance, distance2, distance3);

    vector3df vision = vector3df(intersectionPoint.x,intersectionPoint.y,0);
    vector3df visionDcha = vector3df(intersectionPoint2.x,intersectionPoint2.y,0);
    vector3df visionIzq = vector3df(intersectionPoint3.x,intersectionPoint3.y,0);



    IrrManager::Instance()->getDriver()->setTransform(video::ETS_WORLD, core::IdentityMatrix);
    IrrManager::Instance()->getDriver()->draw3DLine(getPosition(),vision , irr::video::SColor(255, 200, 50, 50) );
    IrrManager::Instance()->getDriver()->draw3DLine(getPosition(),visionDcha , irr::video::SColor(255, 200, 50, 50) );
    IrrManager::Instance()->getDriver()->draw3DLine(getPosition(),visionIzq , irr::video::SColor(255, 200, 50, 50) );
}
void Player::InitializeFuzzyModule(){
  FuzzyVariable& distancia = m_FuzzyModule.CreateFLV("distancia");

  FzSet cerca = distancia.AddLeftShoulderSet("cerca",0,20,40);
  FzSet medio = distancia.AddTriangularSet("medio",20,40,60);
  FzSet lejos = distancia.AddRightShoulderSet("lejos",40,60,110);

  FuzzyVariable& velocidad = m_FuzzyModule.CreateFLV("velocidad");
  FzSet rapido = velocidad.AddRightShoulderSet("mucho", 50, 75, 100);
  FzSet normal = velocidad.AddTriangularSet("medio", 25, 50, 75);
  FzSet lento = velocidad.AddLeftShoulderSet("poco", 0, 25, 50);

  m_FuzzyModule.AddRule(cerca, lento);
  m_FuzzyModule.AddRule(medio, normal);
  m_FuzzyModule.AddRule(lejos,rapido );
}
double Player::GetDeseabilidad(double distancia)
{
  //fuzzify distance and amount of ammo
  m_FuzzyModule.Fuzzify("distancia", distancia);

  m_ultimaVel = m_FuzzyModule.DeFuzzify("velocidad", FuzzyModule::max_av);

  return m_ultimaVel;
}
//---------------------------------------------------------------------------
/**
   IA
*/
void Player::IA(float frente, float izq, float dcha){
    int dir = NINGUNA;

    //if(frente>MUY_LEJOS){  vel = RAPIDO;  }
    //else if(frente>LEJOS){  vel = VEL_MEDIA;  }
    //else if(frente>DIST_MEDIA){  vel = DESPACIO;  }
    //else if(frente>CERCA){  vel = MUY_DESPACIO;  }

    //GIRAR EL COCHE
    if(izq<dcha){
        if(izq <DIST_MEDIA){dir = DERECHA;}
        else if(dcha <DIST_MEDIA){dir = IZQUIERDA;}
    }
    else if(dcha<izq){
        if(dcha <DIST_MEDIA){dir = IZQUIERDA;}
        else if(izq <DIST_MEDIA){dir = DERECHA;}
    }
    //Esta evita que si los dos visores son iguales se choque de frente
    else if(dcha <DIST_MEDIA){
        dir = IZQUIERDA;
    }
    double des = GetDeseabilidad(frente);
    //std::cout<<des<<std::endl;
    //mover((int)frente, dir);
    mover(des, dir);

}
//---------------------------------------------------------------------------
/**
   Mueve
*/
void Player::mover(double vel , int dir){
    b2Vec2 velocidad;
   if(dir == 1){
            cont+= 0.05f;
            body->SetTransform(body->GetPosition(),body->GetAngle()-0.05f);
    }
   if(dir == 2){
            cont-= 0.05f;
            body->SetTransform(body->GetPosition(),body->GetAngle()+0.05f);
    }
    velocidad = b2Vec2(sin(cont)*vel, cos(cont)*vel);
    body->SetLinearVelocity(velocidad);
}
//---------------------------------------------------------------------------
/**
   Salta
*/
void Player::saltar(){
    if(!fingiendoMuerte){
        if(!saltando){
            b2Vec2 velV = body->GetLinearVelocity();
            velV.y = salto;
            body->SetLinearVelocity(velV);
        }
        else if(!dobleSaltando){
            b2Vec2 velV = body->GetLinearVelocity();
            velV.y = salto*3/5;
            body->SetLinearVelocity(velV);
            dobleSaltando = true;
        }
    }
}
//---------------------------------------------------------------------------
/**
   fingirMuerte
*/
void Player::fingirMuerte(){
    if(!fingiendoMuerte){
        b2FixtureDef fixtureDef;
        b2FixtureDef fixtureDef2;
        b2CircleShape circleShape1;
        b2CircleShape circleShape2;

        fingiendoMuerte = true;
        body->DestroyFixture(body->GetFixtureList());
        body->DestroyFixture(body->GetFixtureList());
        body->SetFixedRotation(false);
        circleShape1.m_p.Set(0,-3.f);
        circleShape2.m_p.Set(0,3.f);
        circleShape1.m_radius = tam.X/2;
        circleShape2.m_radius = tam.X/2;
        fixtureDef.shape = &circleShape1;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution  = 0.5f;
        fixtureDef.density  = 1.f;
        personFixture = body->CreateFixture(&fixtureDef);
        personFixture->SetUserData((void*)100);

        fixtureDef2.shape = &circleShape2;
        fixtureDef2.friction = 0.5f;
        fixtureDef2.restitution  = 0.5f;
        fixtureDef2.density  = 5.f;
        body->CreateFixture(&fixtureDef2);

        body->ApplyAngularImpulse(direccion*10000);

    }else{
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape polyShape;
        body->DestroyFixture(body->GetFixtureList());
        body->DestroyFixture(body->GetFixtureList());
        fingiendoMuerte = false;
        polyShape.SetAsBox(tam.X/2,tam.Y/2);
        fixtureDef.shape = &polyShape;
        fixtureDef.friction = 0;
        fixtureDef.restitution  = 0;
        fixtureDef.density  = 10.f;
        body->CreateFixture(&fixtureDef);

        polyShape.SetAsBox(tam.X/4,tam.Y/4,b2Vec2(0,-tam.Y/2), 0);
        fixtureDef.isSensor = true;
        b2Fixture* personajeSensorFixture = body->CreateFixture(&fixtureDef);
        personajeSensorFixture->SetUserData((void*)100);

        body->SetTransform( body->GetPosition(),0);
        body->SetAngularVelocity(0);
        body->SetFixedRotation(true);
        body->ApplyLinearImpulse(b2Vec2(0,10),b2Vec2(0,0));
    }
}
//---------------------------------------------------------------------------
/**
   crearJoint
*/
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
//---------------------------------------------------------------------------
/**
   romperJoint
*/
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
//---------------------------------------------------------------------------
/**
   Getters y setters
*/
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
//---------------------------------------------------------------------------
/**
   Destructor
*/
Player::~Player(){}
