/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          cuboMierda.h

Author:        Estudio Rorschach 
Created:       11/11/2016 Jorge Puerto
Modified:      08/12/2016 Jorge Puerto

Overview:
Pues eso.
*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef CUBOMIERDA_H
#define CUBOMIERDA_H
//---------------------------------------------------------------------------
#include <Box2D/Box2D.h>
#include <irrlicht.h>


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class cuboMierda{
    public:
        cuboMierda(int x, int y);
        void actualiza();
        b2Body* getBody();
        virtual ~cuboMierda();

    protected:

    private:
		IMeshSceneNode* node;
	    b2Body* body;
        int x;
        int y;
};

#endif // CUBOMIERDA_H
