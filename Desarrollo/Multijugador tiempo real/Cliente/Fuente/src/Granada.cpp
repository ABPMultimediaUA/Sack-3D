/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Escopeta.cpp

Author:        Estudio Rorschach
Created:
Modified:      19/12/2016 Miguel Paniagua

Overview:
Clase que contiene el codigo de funcionamiento para la granada.
*******************************************************************************/

#include "Granada.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

#define ARMA 30                     ///< Int para las colisiones de las armas
#define SENSORARMA 35               ///< Int para las colisiones del area cogible de las armas
#define RADTOGRAD 180 / 3.14159265  ///< Conversor de radianes a grados


/******************************************************************************
                               Granada
*******************************************************************************/

//---------------------------------------------------------------------------
/**
   Constructor
*/

Granada::Granada()
{
    siendoCogida= false;
    particulas = new std::vector<b2Body*>();
    mecha = 4000;
    usada = false;
    timerIrr = IrrManager::Instance()->getTimer();
    timergranada = timerIrr->getTime();
    vector3df tam2 = vector3df(5,5,1);
    vector3df tam = vector3df(tam2.X/MPP,tam2.Y/MPP,tam2.Z/MPP);
    node = IrrManager::Instance()->addCubeSceneNode(tam,SColor(30, 100, 30, 0));
    node->setPosition(vector3df(-150/MPP,0/MPP,0/MPP));
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    bodyDef.position.Set(-150/MPP,0);
    bodyDef.type = b2_dynamicBody;

    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.X/2.0f,tam.Y/2.0f);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution  = 0.2f;
    fixtureDef.density  = 2.0f;
    b2Fixture* fixture = body->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)30);
    body->SetFixedRotation(true);
    polyShape.SetAsBox((tam.X*2.0),(tam.Y*2.0));
    fixtureDef.isSensor = true;
    b2Fixture* granadaSensorFixture = body->CreateFixture(&fixtureDef);
    granadaSensorFixture->SetUserData((void*)35);
}

//---------------------------------------------------------------------------
/**
   Metodo que actualiza la posicion y rotacion del arma
*/
void Granada::actualiza(){

    if(siendoCogida && PhysicWorld::Instance()->getPlayer()->getCogiendo()){
        int dir = PhysicWorld::Instance()->getPlayer()->getDireccion();
        node->setPosition(vector3df(body->GetPosition().x+((5.0f/MPP)*dir),body->GetPosition().y,0));
    }
    else node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));

    node->setRotation(vector3df(0,0,body->GetAngle()*RADTOGRAD));

    if((timerIrr->getTime() - timergranada > mecha)&& usada){
        //std::cout<<"EXPLOTADA"<<std::endl;
        int numRays = 10;
        for (int i = 0; i < numRays; i++) {
              float angle = (i / (float)numRays) * 360;
              b2Vec2 rayDir( sinf(angle), cosf(angle) );

              b2BodyDef* bd = new b2BodyDef();
              bd->type = b2_dynamicBody;
              bd->bullet = true; // prevent tunneling at high speed
              bd->linearDamping = 10; // drag due to moving through air
              bd->gravityScale = 0; // ignore gravity
              bd->position = body->GetPosition(); // start at blast center
              bd->linearVelocity = 500/MPP * rayDir;
              b2Body* Partbody = PhysicWorld::Instance()->GetWorld()->CreateBody(bd);

              b2CircleShape circleShape;
              circleShape.m_radius = 40.05f/MPP; // very small

              b2FixtureDef* fd = new b2FixtureDef();
              fd->shape = &circleShape;
              fd->density = 60; // very high - shared across all particles
              fd->friction = 0; // friction not necessary
              fd->restitution = 0.99f; // high restitution to reflect off obstacles
                /*
              fd->filter.categoryBits = 4;
              fd->filter.maskBits = 3;
                */
              fd->filter.groupIndex = -1; // particles should not collide with each other

              b2Fixture* fdd = Partbody->CreateFixture(fd);
              fdd->SetUserData((void*)88);
                particulas->insert(particulas->begin(),Partbody);
              delete fd;
        }
        usada = false;
        timergranada = timerIrr->getTime();
    }


    if((timerIrr->getTime() - timergranada > (100))){

         for (int i=0; i<particulas->size(); i++){
            particulas->at(i)->DestroyFixture(particulas->at(i)->GetFixtureList());
    std::cout<<"EXPLOTADA"<<std::endl;
         }
         particulas->clear();
    }
}
//---------------------------------------------------------------------------
/**
   Metodo que ejecuta el usar de la clase
*/
void Granada::usar(){

        PhysicWorld::Instance()->getPlayer()->romperJoint();

        timergranada = timerIrr->getTime();
        usada=true;

}
//---------------------------------------------------------------------------
/**
   Getters and setters
*/
b2Body* Granada::getBody(){return body;}
void Granada::setCogida(bool aux){

    vector3df tam2 = vector3df(5,3,1);
    vector3df tam = vector3df(tam2.X/MPP,tam2.Y/MPP,tam2.Z/MPP);
    body->DestroyFixture(body->GetFixtureList());
    body->DestroyFixture(body->GetFixtureList());
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    b2Fixture* armaSensorFixture;
    b2Fixture* fixture;
    if(aux){
        polyShape.SetAsBox(tam.X/2.0f,tam.Y/2.0f);
        fixtureDef.shape = &polyShape;
        fixtureDef.density  = 0.1f;
        fixtureDef.isSensor = true;
        fixture = body->CreateFixture(&fixtureDef);
        fixture->SetUserData((void*)30);
        body->SetFixedRotation(true);
        polyShape.SetAsBox((tam.X/4.0f),(tam.Y/4.0f));
        fixtureDef.isSensor = true;
        armaSensorFixture = body->CreateFixture(&fixtureDef);
        armaSensorFixture->SetUserData((void*)35);
    }
    else{
        b2PolygonShape polyShape;
        polyShape.SetAsBox(tam.X/2.0f,tam.Y/2.0f);
        fixtureDef.shape = &polyShape;
        fixtureDef.friction = 0.5f;
    fixtureDef.restitution  = 0.2f;
    fixtureDef.density  = 2.0f;
        fixture = body->CreateFixture(&fixtureDef);
        fixture->SetUserData((void*)30);
        body->SetFixedRotation(true);
        polyShape.SetAsBox((tam.X*2.0),(tam.Y*2.0));
        fixtureDef.isSensor = true;
        armaSensorFixture = body->CreateFixture(&fixtureDef);
        armaSensorFixture->SetUserData((void*)35);
    }
    siendoCogida = aux;
}
bool Granada::getCogida(){return siendoCogida;}
//---------------------------------------------------------------------------
/**
   Destructor
*/

Granada::~Granada()
{
    //dtor
}
