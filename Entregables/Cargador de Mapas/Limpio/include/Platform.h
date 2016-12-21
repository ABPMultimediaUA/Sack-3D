/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Platform.h

Author:        Estudio Rorschach 
Created:       11/11/2016 Jorge Puerto
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que define una plataforma, con sus componentes grafica y fisica.

*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef PLATFORM_H
#define PLATFORM_H
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
                               Platform
*******************************************************************************/
class Platform{
    public:
        Platform(vector3df pos, vector3df tam,SColor color); 	///< Constructor		
        b2Fixture* getPlatformFixture();       
        IMeshSceneNode* getNode();         						///< Getter del nodo irrlicht
        b2Body* getBody();                 ///< Getter del body                                      																	
        virtual ~Platform();									///< Destructor	
    
    protected:                                                      
        IMeshSceneNode* node;              ///< 

    private:																								
    	IMesh* mesh;											///< Malla													
	    b2Body* body;											///< Cuerpo fisico													
	    b2Fixture* platformFixture;
};																								
																								
#endif // PLATFORM_H
