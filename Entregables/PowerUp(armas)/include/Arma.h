/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Arma.h

Author:        Estudio Rorschach
Created:
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que contiene el codigo de funcionamiento para las armas.
*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef ARMA_H
#define ARMA_H
//---------------------------------------------------------------------------
#include <Box2D/Box2D.h>
#include <irrlicht.h>

#include "Usable.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/******************************************************************************
                               Arma
*******************************************************************************/
class Arma : public Usable{
    public:
        Arma();					///< Constructor
        void actualiza();		///< actualiza la posicion y rotacion del arma
        void usar();            ///< ejecuta el usar de la clase
        b2Body* getBody();		///< Getter del body
        virtual ~Arma();		///< Destructor

    protected:

    private:
        IMeshSceneNode* node;	///< Nodo irrlicht para poder mover, dibujar, etc.
	    b2Body* body;			///< Cuerpo fisico box2d para poder aplicar fisicas
};

#endif // ARMA_H
