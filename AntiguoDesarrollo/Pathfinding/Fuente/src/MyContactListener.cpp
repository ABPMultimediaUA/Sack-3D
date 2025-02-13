/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          MyContactListener.cpp

Author:        Estudio Rorschach
Created:
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que contiene los listeners necesarios para obtener e interpretar la
informacion de las colisiones que suceden en el juego.
*******************************************************************************/
#include "MyContactListener.h"
#include "PhysicWorld.h"

#define PLAYER 10			///< Int para saber cuando colisiona el personaje
#define PIESPLAYER 100		///< Int para saber si el personaje esta tocando suelo
#define ARMA 30				///< Int para las colisiones de las armas
#define SENSORARMA 35		///< Int para las colisiones del area cogible de las armas
#define BALA 40				///< Int para las colisiones de las balas

/******************************************************************************
                               MyContactListener
*******************************************************************************/


//---------------------------------------------------------------------------
/**
   Constructor
*/
MyContactListener::MyContactListener(){}
//---------------------------------------------------------------------------
/**
   Esta clase nos detecta cuando una colision comienza.
   Recibe un objeto b2Contact del cual podemos obtener la informacion
   de los 2 objetos que colisionan (A y B), los cuales para saber cual
   es cual tenemos que acceder a sus respectivos metodos GetUserData
   y tener en cuenta siempre que tanto A como B pueden ser de cualquier
   tipo.
*/
void MyContactListener::BeginContact(b2Contact* contact){
	 void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
     void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();
}
//---------------------------------------------------------------------------
/**
   Esta clase nos detecta cuando una colision termina y funciona como la anterior.
*/
void MyContactListener::EndContact(b2Contact* contact){
    void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
    void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();
}
//---------------------------------------------------------------------------
/**
   Destructor
*/
MyContactListener::~MyContactListener(){}
