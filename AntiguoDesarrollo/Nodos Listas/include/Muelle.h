/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Muelle.h

Author:        Estudio Rorschach
Created:       12/12/2016 Miguel Cordoba
Modified:      12/12/2016 Miguel Cordoba

Overview:
Clase que define un muelle, con sus componentes grafica y fisica.

*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef MUELLE_H
#define MUELLE_H
//---------------------------------------------------------------------------
#include <Box2D/Box2D.h>
#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


/******************************************************************************
                               Muelle
*******************************************************************************/
class Muelle{
    public:
        Muelle(float f , vector3df pos, vector3df tam = vector3df(10, 5, 10),SColor color = SColor(255, 0, 255, 0)); 	///< Constructor
        float getFuerza();                                    ///< Getter
        b2Body* getBody();                                  ///< Getter
        virtual ~Muelle();									///< Destructor
    private:
    	IMesh* mesh;											///< Malla
	    b2Body* body;											///< Cuerpo fisico
	    float fuerza;                                             ///< Fuerza del impulso del muelle
};

#endif // MUELLE_H
