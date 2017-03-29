/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Teleport.h

Author:        Estudio Rorschach
Created:       12/12/2016 Miguel Cordoba
Modified:      12/12/2016 Miguel Cordoba

Overview:
Clase que define un Teletransportador, con sus componentes grafica y fisica.

*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef TELEPORT_H
#define TELEPORT_H
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
                               Teleport
*******************************************************************************/
class Teleport{
    public:
        Teleport(int i, int p, vector3df pos, vector3df tam = vector3df(2, 20, 5) ,SColor color = SColor(255, 255, 255, 0)); 	///< Constructor
        b2Body* getBody();                                      ///< Getter
        int getTeleportId();                                    ///< Getter
        int getTeleportPartnerId();                             ///< Getter
        virtual ~Teleport();									///< Destructor
    private:
    	IMesh* mesh;											///< Malla
	    b2Body* body;											///< Cuerpo fisico
	    int id;                                                 ///< identificador del teleport
	    int partner;                                            ///< Teleport al que apunta
};

#endif // PLATFORM_H
