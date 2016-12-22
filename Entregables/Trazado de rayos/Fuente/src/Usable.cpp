/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Usable.cpp

Author:        Estudio Rorschach 
Created:       11/11/2016 Jorge Puerto
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que hereda de cogible e implementa lo necesario para que un 
objeto se pueda usar, es decir el player sea capaz de realizar una accion
con el. 
*******************************************************************************/

#include "Usable.h"

/******************************************************************************
                               Usable
*******************************************************************************/
//---------------------------------------------------------------------------
/**
   Constructor
*/
Usable::Usable(){
    expuesto = true;
	expuesto = false;
}
//---------------------------------------------------------------------------
/**
   getters y setters
*/
void Usable::setExpuesto(bool aux){expuesto = aux;}
bool Usable::getExpuesto(){return expuesto;}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Usable::~Usable(){}
