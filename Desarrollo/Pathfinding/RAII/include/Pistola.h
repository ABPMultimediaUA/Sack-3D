/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Pistola.h

Author:        Estudio Rorschach
Created:       08/12/2016 Jorge Puerto
Modified:      09/01/2017 Miguel Cordoba

Overview:
Clase que contiene el codigo de funcionamiento para las Pistolas.
*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef PISTOLA_H
#define PISTOLA_H
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
                               Pistola
*******************************************************************************/
class Pistola: public Usable{
    public:
        Pistola(int modelo,vector3df pos); ///< Constructor
        void actualiza();		           ///< actualiza la posicion y rotacion del Pistola
        b2Body* getBody();		           ///< Getter del body
        void setCogida(bool aux);
        bool getCogida();
        void usar();                       ///< ejecuta el usar de la clase
        virtual ~Pistola();		           ///< Destructor

    protected:

    private:
        IMeshSceneNode* node;	           ///< Nodo irrlicht para poder mover, dibujar, etc.
	    b2Body* body;			           ///< Cuerpo fisico box2d para poder aplicar fisicas
        bool siendoCogida;                 ///< Booleano que indicara si esta siendo cogida
};

#endif // Pistola_H
