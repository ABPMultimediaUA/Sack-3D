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
#include "Bala.h"
#include "Map.h"
#include "Platform.h"
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
        void creaCuboMierda(int x, int y);       ///< ????????    
        b2World* GetWorld();                     ///< Getter            
        std::vector<cuboMierda*>* GetCubos();    ///< Getter                            
        std::vector<Bala*>* GetBalas();          ///< Getter                    
        std::vector<Platform*>* getPlatforms();  ///< Getter                    
        Player* getPlayer();                     ///< Getter            
        Bot* getBot();                           ///< Getter    
        Arma* getArma();                         ///< Getter
        Map* getMap();        
        void setPlayer(Player* jugador);         ///< Setter                        
        void setBot(Bot* jugador);               ///< Setter                
        void setArma(Arma* arma);                ///< Setter                
        virtual ~PhysicWorld();                  ///< Setter 
        int getJugadores();
        void crearMapa(int numero);

        //ToDo: esto hay que quitarlo de aqui
        b2RevoluteJoint* joint;

    private:
        static PhysicWorld* pinstance;           ///< instancia del mundo                                          
        b2World* world;                          ///< variable mundo de box2d              
        MyContactListener* contactListener;      ///< detector de colisiones                               
        std::vector<cuboMierda*>* cubos;         ///< eso                              
        std::vector<Bala*>* balas;               ///< Array de balas
        std::vector<Platform*>* platforms;       ///< Array de plataformas                                      
        Arma* arma;                              ///< arma
        Map* mapa;                                         
        Player* jugador1 = 0;                    ///<                   
        Bot* bot1 = 0;                           ///<           
};

#endif // PHYSICWORLD_H
