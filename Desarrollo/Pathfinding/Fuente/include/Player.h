/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Player.h

Author:        Estudio Rorschach
Created:       11/11/2016 Jorge Puerto
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que define un player
*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef PLAYER_H
#define PLAYER_H
//---------------------------------------------------------------------------
#include <Box2D/Box2D.h>
#include <irrlicht.h>
#include "MyEventReceiver.h"
#include "fuzzy/FuzzyModule.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/******************************************************************************
                               Player
*******************************************************************************/
class Player{
    public:
        Player(vector3df pos);                   ///< Constructor
        void update();                           ///< Actualizar
        void mover(double vel, int dir);                            ///< Mover
        void moverJugador(int, int);
        vector3df getPosition();                 ///< Getter
        b2Body* getBody();                       ///< Getter
        virtual ~Player();                       ///< Destructor

    protected:
        IMeshSceneNode* node;            ///<
        b2Body* body;                            ///<
        b2PolygonShape* polyShape;               ///<
        b2Fixture* personFixture;                ///<
        b2RevoluteJoint* joint;                  ///<
        b2RevoluteJointDef* jointDef;            ///<
		MyEventReceiver* eventReceiver;          ///<
    private:
};

#endif // PLAYER_H
