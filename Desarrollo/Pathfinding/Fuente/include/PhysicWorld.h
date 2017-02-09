/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          PhysicWorld.h

Author:        Estudio Rorschach
Created:
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que contiene el mundo fisico, en el se trata todo lo relacionado con la fisica.
*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef PHYSICWORLD_H
#define PHYSICWORLD_H
//---------------------------------------------------------------------------
#include <Box2D/Box2D.h>
#include <iostream>
#include "PhysicWorld.h"
#include "cuboMierda.h"
#include "Player.h"
#include "Bot.h"
#include "MyContactListener.h"
#include "Arma.h"
#include "Map.h"
#include "Bala.h"
#include <vector>

/******************************************************************************
                               Arma
*******************************************************************************/
class PhysicWorld{
    public:
        static PhysicWorld* Instance();          ///< Devuelve la unica instancia de la clase
        PhysicWorld();                           ///< Constructor
        b2Body* CreateBox(int x,int y);          ///< Genera una caja
        void Step(float DeltaTime);              ///< Actualiza un instante en el mundo fisico
        void ClearForces();                      ///< ????????
        b2World* GetWorld();                     ///< Getter
        Player* getPlayer();                     ///< Getter
        Player* getObjetivo();                     ///< Getter
        Map* getMapa();
        void setPlayers(Player* c, Player* o);         ///< Setter
        void setMapa(Map* mapa);         ///< Setter
        virtual ~PhysicWorld();                  ///< Setter

        //ToDo: esto hay que quitarlo de aqui
        b2RevoluteJoint* joint;

    private:
        static PhysicWorld* pinstance;           ///< instancia del mundo
        b2World* world;                          ///< variable mundo de box2d
        MyContactListener* contactListener;      ///< detector de colisiones
        Player* jugador1 = 0;                    ///<
        Player* objetivo = 0;                    ///<
        Map* mapa=0;
};

#endif // PHYSICWORLD_H
