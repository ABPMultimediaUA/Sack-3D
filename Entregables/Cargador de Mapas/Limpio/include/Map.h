/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Map.h

Author:        Estudio Rorschach 
Created:       
Modified:      08/12/2016 Jorge Puerto

Overview:

*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef MAP_H
#define MAP_H
//---------------------------------------------------------------------------
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/******************************************************************************
                               Map
*******************************************************************************/
class Map{
    public:
        Map(int numero);		///< Constructor
        void cargarMapa(stringw file);
        void elegirMapa(int numero);
        int getMapa();
        void setMapa(int numero);		
        virtual ~Map();			///< Destructor	
    private:
    	int numMapa;
};

#endif // MAP_H
