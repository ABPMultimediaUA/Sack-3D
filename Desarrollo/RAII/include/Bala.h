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
        Bala(irr::core::vector3df, int, int, float, int);               ///< Constructor
        void actualiza();                  ///< actualiza la posicion de la bala
        b2Body* getBody();                 ///< Getter del body
        IMeshSceneNode* getNode();         ///< Getter del nodo irrlicht
        b2Fixture* getbalaFixture();       ///< Getter del fixture de la bala
        void teletransportar();            ///< Teletrasporta al cubo a la posicion nextPos
        void setNextPos(b2Vec2 pos);       ///< Setter
        int getTime();                     ///< Getter del tiempo
        int getTimeVida();                 ///< Getter del tiempo de vida
        virtual ~Bala();                   ///< Destructor

        int tiempoVida;                    ///<
        int velocidad;                     ///<
        float desviacion;                     ///<
        irr::f32 timerbala;                     ///<
        ITimer* timerIrr;                  ///<

    protected:
        IMeshSceneNode* node;              ///<
	    b2Body* body;                      ///<
        b2Fixture* balaFixture;            ///<
        b2Vec2 nextPos;                    ///< La posicion a la que debe teletransportarse la siguiente vez que se actualice
		bool teletransportado;             ///< Booleano que indica que ha pisado un teletransporte

    private:
};

#endif // BALA_H
