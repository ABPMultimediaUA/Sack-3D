/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          IEventReceiver.h

Author:        Estudio Rorschach
Created:       11/11/2016 Jorge Puerto
Modified:      12/12/2016 Miguel Cordoba

Overview:
Clase que controla los eventos que se producen por teclado, raton, controles...

*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H
//---------------------------------------------------------------------------
#include <Box2D/Box2D.h>
#include <iostream>
#include <irrlicht.h>
#include "cuboMierda.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/******************************************************************************
                               IEventReceiver
*******************************************************************************/
class MyEventReceiver: public IEventReceiver{
     public:
     	MyEventReceiver();									///< Constructor
     	virtual bool OnEvent(const SEvent& event);			///< Manejador de eventos
        virtual ~MyEventReceiver();							///< Destructor
		virtual bool IsKeyDown(EKEY_CODE keyCode)const; 	///< Indica si la tecla esta pulsada
    private:
    	bool KeyIsDown[KEY_KEY_CODES_COUNT];				///< Vector de teclas
};

#endif // MYEVENTRECEIVER_H
