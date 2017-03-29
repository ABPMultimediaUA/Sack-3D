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
#ifndef ESCOPETA_H
#define ESCOPETA_H
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
                               Escopeta
*******************************************************************************/

class Escopeta: public Usable{
    public:
        Escopeta(vector3df pos);				///< Constructor
        void actualiza();		///< actualiza la posicion y rotacion del arma
        void usar();            ///< ejecuta el usar de la clase
        f32 timerescopeta;      ///<
        ITimer* timerIrr;       ///<
        bool getConUsos();		///< Getter de usos
        b2Body* getBody();		///< Getter del body
        virtual ~Escopeta();	///< Destructor


    protected:

    private:
        IMeshSceneNode* node;	///< Nodo irrlicht para poder mover, dibujar, etc.
	    b2Body* body;			///< Cuerpo fisico box2d para poder aplicar fisicas
	    int cadencia;
	    int usos;
	    bool conUsos;
};

#endif // ESCOPETA_H
