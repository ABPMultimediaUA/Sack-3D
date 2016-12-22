/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Bala.h

Author:        Estudio Rorschach 
Created:       
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que contiene el codigo de funcionamiento para las balas.
*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef BALA_H
#define BALA_H
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
                               Bala
*******************************************************************************/
class Bala{
    public:
        Bala();                            ///< Constructor                         
        void actualiza();                  ///< actualiza la posicion de la bala                                      
        b2Body* getBody();                 ///< Getter del body                                      
        IMeshSceneNode* getNode();         ///< Getter del nodo irrlicht                                             
        b2Fixture* getbalaFixture();       ///< Getter del fixture de la bala                                                     
        int getTime();                     ///< Getter del tiempo                                 
        int getTimeVida();                 ///< Getter del tiempo de vida                                     
        virtual ~Bala();                   ///< Destructor                                     
                                                        
        int tiempoVida;                    ///<                                  
        int velocidad;                     ///<                                  
        f32 timerbala;                     ///<                                  
        ITimer* timerIrr;                  ///<                                      
                                                        
    protected:                                                      
        IMeshSceneNode* node;              ///<                                          
	    b2Body* body;                      ///<                                 
	    b2Fixture* balaFixture;           ///<                                             

    private:
};

#endif // BALA_H
