/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Camera.h

Author:        Estudio Rorschach
Created:
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que contiene el codigo de funcionamiento para la camara.
*******************************************************************************/
//---------------------------------------------------------------------------

#ifndef CAMERA_H
#define CAMERA_H
//---------------------------------------------------------------------------
#include "IrrManager.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/******************************************************************************
                               Camera
*******************************************************************************/
class Camera{
    public:
        Camera();						///< Constructor
        setPosition(vector3df pos);		///< Setter
        setTarget(vector3df pos); 		///< Setter
        update(float time); 			///< Actualizar
        virtual ~Camera();				///< Destructor


    protected:

    private:
    	ICameraSceneNode* camera;		///< Nodo irrlicht
        ITimer* timer;                  ///< Controla el tiempo del bucle
        float tiempoTransc;             ///< Indicara el tiempo transcurrido entre iteraciones
        float updateT;
        double porcentUpdate;
        double porcentGap;
        std::vector<vector3df>* flowCam;
        vector3df* cenAnt;
        vector3df* cenSig;
};

#endif // CAMERA_H
