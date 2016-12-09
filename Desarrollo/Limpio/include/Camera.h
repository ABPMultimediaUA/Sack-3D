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

/******************************************************************************
                               Camera
*******************************************************************************/
class Camera{
    public:
        Camera();						///< Constructor					
        setPosition(vector3df pos);		///< Setter									
        setTarget(vector3df pos); 		///< Setter									
        update(); 						///< Actualizar					
        virtual ~Camera();				///< Destructor		
							

    protected:

    private:
    	ICameraSceneNode* camera;			///< Nodo irrlicht
};

#endif // CAMERA_H
