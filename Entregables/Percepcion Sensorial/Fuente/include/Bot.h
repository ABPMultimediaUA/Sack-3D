/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Bot.h

Author:        Estudio Rorschach 
Created:       
Modified:      08/12/2016 Jorge Puerto

Overview:

*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef BOT_H
#define BOT_H
//---------------------------------------------------------------------------
#include <Player.h>
#include <Box2D/Box2D.h>
#include <irrlicht.h>
#include "IrrManager.h"
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/******************************************************************************
                               Bot
*******************************************************************************/
class Bot : public Player
{
    public:
        Bot(vector3df pos);                          ///< Constructor                 
        void update();                               ///<            
        int getMemership(float d);                   ///<                        
        int getMayorValor(int x1, int x2, int x3);   ///<                                        
        void huir(int dir);                          ///<                
        void quieto();                               ///<            
        virtual ~Bot();                              ///<            

    protected:

    private:
    	float distancia;                             ///<                     
    	float membership;                            ///<                     
    	int cerca;                                   ///<             
    	int intermedio;                              ///<                     
    	int lejos;                                   ///<             
};                                                  

#endif // BOT_H
