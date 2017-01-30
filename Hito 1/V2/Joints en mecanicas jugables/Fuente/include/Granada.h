/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Arma.h

Author:        Estudio Rorschach
Created:
Modified:      19/12/2016 Miguel Paniagua

Overview:
Clase que contiene el codigo de funcionamiento para la granada.
*******************************************************************************/
//---------------------------------------------------------------------------

#ifndef GRANADA_H
#define GRANADA_H
//---------------------------------------------------------------------------
#include <Box2D/Box2D.h>
#include <irrlicht.h>
#include <vector>
#include "Usable.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/******************************************************************************
                               Granada
*******************************************************************************/
class Granada:public Usable{
    public:
        Granada();
        void actualiza();		///< actualiza la posicion y rotacion del arma
        void usar();            ///< ejecuta el usar de la clase
        f32 timergranada;       ///<
        ITimer* timerIrr;       ///<
        b2Body* getBody();		///< Getter del body
        virtual ~Granada();

    protected:
        IMeshSceneNode* node;	///< Nodo irrlicht para poder mover, dibujar, etc.
	    b2Body* body;			///< Cuerpo fisico box2d para poder aplicar fisicas
	    int mecha;
	    bool usada;
        std::vector<b2Body*>* particulas;

    private:
};

#endif // GRANADA_H
