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
        int getMayorValor(float x1, float x2, float x3);   ///<
        float getMayorPeligro(float x1, float x2);   ///<
        void huir();                          ///<
        void getJugadorCerca();
        void buscarJugadorCerca();
        void atacar();
        void buscarArma();
        void quieto();                               ///<
        float calcularPeligro();                      ///< Calcular peligro
        void calcularAccion(float peligro);             ///< Calcular accion a realizar
        float valorarDistancia(b2Body*, b2Body*);       ///< distancia entre dos bodys.
        int getNumJugadores();                        ///< get total de player

        virtual ~Bot();                              ///<

    protected:

    private:
    	float distancia;                             ///<
    	float membership;                            ///<
    	float cerca;                                   ///<
    	float intermedio;                              ///<
    	float lejos;                                   ///<
};

#endif // BOT_H
