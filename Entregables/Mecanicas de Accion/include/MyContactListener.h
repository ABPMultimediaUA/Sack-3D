/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          MyContactListener.h

Author:        Estudio Rorschach 
Created:       
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que contiene los listeners necesarios para obtener e interpretar la 
informacion de las colisiones que suceden en el juego.
*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H
//---------------------------------------------------------------------------
#include "Box2D/Box2D.h"
#include <iostream>

/******************************************************************************
                               MyContactListener
*******************************************************************************/
class MyContactListener: public b2ContactListener{
    public:
        MyContactListener();					///< Constructor
        virtual ~MyContactListener();			///< Destructor
        void BeginContact(b2Contact* contact);	///< Comienza contacto
        void EndContact(b2Contact* contact);	///< Termina contacto


    protected:

    private:
};

#endif // MYCONTACTLISTENER_H
