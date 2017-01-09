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
#include "fuzzy/FuzzyModule.h"



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
        void InicializarFuzzy();
                         ///<
        void quieto();                               ///<
        void mover();
        void seguirCamino(int i);                        ///< metodo ficticio que hace que se mueva el bot por el momento
        double GetPeligro();
        double getDistancia(b2Body* a, b2Body* b);


        virtual ~Bot();                              ///<

    protected:
        FuzzyModule m_FuzzyModule;
        double danger;
    private:

};

#endif // BOT_H
