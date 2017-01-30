/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Cogible.cpp

Author:        Estudio Rorschach 
Created:       
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que define lo minimo para que un objeto que se pueda coger, heredaran de 
esta todos los objetos que se puedan coger y ademas tengan funcionalidades propias.
*******************************************************************************/

#include "Cogible.h"

/******************************************************************************
                               Cogible
*******************************************************************************/
//---------------------------------------------------------------------------
/**
   Constructor
*/
Cogible::Cogible(){
    cogido = false;
}


//---------------------------------------------------------------------------
/**
   Getters y setters
*/
bool Cogible::getCogido(){return cogido;}
void Cogible::setCogido(bool aux){cogido = aux;}

//---------------------------------------------------------------------------
/**
   Destructor
*/
Cogible::~Cogible(){}
