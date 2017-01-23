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
#include "MyContactListener.h"
#include "Arma.h"
#include "Bala.h"
#include "Muelle.h"
#include "Teleport.h"
#include <vector>
#define MPP       64
#define PPM       1/64
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
        void creaCuboMierda(int x, int y);       ///< ????????
        b2World* GetWorld();                     ///< Getter
        std::vector<cuboMierda*>* GetCubos();    ///< Getter
        std::vector<Bala*>* GetBalas();          ///< Getter
        Player* getPlayer();                     ///< Getter
        Arma* getArma();                         ///< Getter
        std::vector<Cogible*>* GetCogibles();    ///< Getter
        std::vector<Muelle*>* GetMuelles();      ///< Getter
        std::vector<Teleport*>* GetTeletransportes();      ///< Getter
        void setPlayer(Player* jugador);         ///< Setter
        void setArma(Arma* arma);                ///< Setter
        void setCogibles(std::vector<Cogible*>* aux);          ///< Setter
        virtual ~PhysicWorld();                  ///< Setter

        //ToDo: esto hay que quitarlo de aqui
        b2RevoluteJoint* joint;

    private:
        static PhysicWorld* pinstance;           ///< instancia del mundo
        b2World* world;                          ///< variable mundo de box2d
        MyContactListener* contactListener;      ///< detector de colisiones
        std::vector<cuboMierda*>* cubos;         ///< eso
        std::vector<Bala*>* balas;               ///< Array de balas
        std::vector<Cogible*>* cogibles;         ///< Array de cogibles
        std::vector<Muelle*>* muelles;           ///< Array de muelles
        std::vector<Teleport*>* teletransportes; ///< Array de teletransportes
        Arma* arma;                              ///< arma
        Player* jugador1 = 0;                    ///<
};

#endif // PHYSICWORLD_H
