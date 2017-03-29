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
#define DECELERATIX        50
#define MUY_LEJOS          50
#define LEJOS              40
#define DIST_MEDIA         30
#define CERCA              20
#define MUY_CERCA          10
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
    jointDef = NULL;
    vector3df tam = vector3df(10, 10,10);
    node = IrrManager::Instance()->addCubeSceneNode(tam, SColor(255, 255, 0, 0));
    node->setPosition(pos);

    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;

    bodyDef.position.Set(pos.X,pos.Y);
    bodyDef.type = b2_kinematicBody;

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
    eventReceiver = IrrManager::Instance()->getEventReciever();
}
//---------------------------------------------------------------------------
/**
   Actualiza posicion y rotacion
*/
void Player::update(){
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));

}
//---------------------------------------------------------------------------
/**
   IA
*/

//---------------------------------------------------------------------------
/**
   Mueve
*/
void Player::mover(double vel , int dir){
    if(vel == 1)
        body->SetTransform(b2Vec2 (body->GetPosition().x+(dir*10), body->GetPosition().y ),body->GetAngle());
    else
        body->SetTransform(b2Vec2 (body->GetPosition().x, body->GetPosition().y+(dir*10) ),body->GetAngle());

     //std::cout<<"Posicion objetivo: "<<body->GetPosition().x+5<<" "<<body->GetPosition().y+5<<std::endl;
}
void Player::moverJugador(int x, int y){
    int avanceX = 0;
    int avanceY = 0;

    if(x==0 && y == 0){}
    else{
        //std::cout<<"Posicion Jugador: "<<body->GetPosition().x-5<<" "<<(body->GetPosition().y*-1)+5<<std::endl;
        //std::cout<<"Posicion Nodo: "<<x*10<<" "<<y*10<<std::endl;

        //body->SetTransform(b2Vec2 (body->GetPosition().x+10, body->GetPosition().y ),body->GetAngle());
        if((body->GetPosition().y*-1)-5 > (x*10)) avanceY = +10;
        if((body->GetPosition().y*-1)-5 < (x*10)) avanceY = -10;

        if(body->GetPosition().x-5 > (y*10)) avanceX = -10;
        if(body->GetPosition().x-5 < (y*10)) avanceX = +10;

        body->SetTransform(b2Vec2 (body->GetPosition().x+avanceX, body->GetPosition().y +avanceY),body->GetAngle());
    }
}
//---------------------------------------------------------------------------
/**
   Getters y setters
*/
b2Body* Player::getBody(){return body;}
vector3df Player::getPosition(){return vector3df(body->GetPosition().x,body->GetPosition().y,0);}

//---------------------------------------------------------------------------
/**
   Destructor
*/
Player::~Player(){}
