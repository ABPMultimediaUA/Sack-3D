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
#include "Player.h"
#include "MyContactListener.h"
#include "Pistola.h"
#include "Escopeta.h"
#include "Granada.h"
#include "Bala.h"
#include "Muelle.h"
#include "Teleport.h"
#include "GameResource.h"
#include <vector>
#include "Map.h"
#include "Camera.h"
#define MPP                    64
#define PPM                    1/64
#define MAX_NUM_TELEPORT       10
#define MAX_NUM_PLAYER         4
#define MAX_NUM_PISTOLA        20
#define MAX_NUM_ESCOPETA       20
#define MAX_NUM_GRANADA        20
#define MAX_NUM_BALA           80
#define MAX_NUM_MUELLE         20

/******************************************************************************
                               Pistola
*******************************************************************************/
class PhysicWorld{
    public:
        static PhysicWorld* Instance();          ///< Devuelve la unica instancia de la clase
        PhysicWorld();                           ///< Constructor
        void inicializaVariables();
        b2Body* CreateBox(int x,int y);          ///< Genera una caja
        void Step(float DeltaTime);              ///< Actualiza un instante en el mundo fisico
        void ClearForces();                      ///< ????????
        void creaCuboMierda(int x, int y);       ///< ????????
        b2World* GetWorld();                     ///< Getter
        std::vector<Bala*>* GetBalas();          ///< Getter
        Player* getPlayer(int);                     ///< Getter
        Pistola* getPistola();                         ///< Getter
        std::vector<Cogible*>* GetCogibles();    ///< Getter
        std::vector<Muelle*>* GetMuelles();      ///< Getter
        std::vector<Teleport*>* GetTeletransportes();      ///< Getter
        void setPistola(Pistola* Pistola);                ///< Setter
        void setCogibles(std::vector<Cogible*>* aux);          ///< Setter
        void Actualiza(float TimeStamp);
        GameResource<Teleport>* CreateTeleport(Teleport *tp = nullptr){
            for (int i = 0; i < MAX_NUM_TELEPORT; ++i){
                if(m_teletransportes[i].Get()== nullptr){
                    m_teletransportes[i].Reset(tp);
                    return &m_teletransportes[i];
                }
            }
        }
        GameResource<Muelle>* CreateMuelle(Muelle *tp = nullptr){
            for (int i = 0; i < MAX_NUM_MUELLE; ++i){
                if(m_Muelles[i].Get()== nullptr){
                    m_Muelles[i].Reset(tp);
                    return &m_Muelles[i];
                }
            }
        }
        GameResource<Pistola>* CreatePistola(Pistola *tp = nullptr){
            for (int i = 0; i < MAX_NUM_PISTOLA; ++i){
                if(m_Pistolas[i].Get()== nullptr){
                    m_Pistolas[i].Reset(tp);
                    return &m_Pistolas[i];
                }
            }
        }
        GameResource<Escopeta>* CreateEscopeta(Escopeta *tp = nullptr){
            for (int i = 0; i < MAX_NUM_ESCOPETA; ++i){
                if(m_Escopetas[i].Get()== nullptr){
                    m_Escopetas[i].Reset(tp);
                    return &m_Escopetas[i];
                }
            }
        }
        GameResource<Granada>* CreateGranada(Granada *tp = nullptr){
            for (int i = 0; i < MAX_NUM_GRANADA; ++i){
                if(m_Granadas[i].Get()== nullptr){
                    m_Granadas[i].Reset(tp);
                    return &m_Granadas[i];
                }
            }
        }
        //template<class Obj> GameResource<Obj>* CreateObject(Obj *obj = nullptr){
        //    if(Teleport* tp = static_cast<Teleport*>(obj)){
        //        for (int i = 0; i < MAX_NUM_TELEPORT; ++i){
        //            if(m_teletransportes[i].Get()== nullptr){
        //                m_teletransportes[i].Reset(tp);
        //                return &m_teletransportes[i];
        //            }
        //        }
        //    }
        //    else if(Muelle* tp = static_cast<Muelle*>(obj)){
        //        for (int i = 0; i < MAX_NUM_MUELLE; ++i){
        //            if(m_Muelles[i].Get()== nullptr){
        //                m_Muelles[i].Reset(tp);
        //                return &m_Muelles[i];
        //            }
        //        }
        //    }
        //    return nullptr;
        //}
        virtual ~PhysicWorld();                  ///< Setter

        //ToDo: esto hay que quitarlo de aqui
        b2RevoluteJoint* joint;

    private:
        static PhysicWorld* pinstance;           ///< instancia del mundo
        b2World* world;                          ///< variable mundo de box2d
        MyContactListener* contactListener;      ///< detector de colisiones
        std::vector<Bala*>* balas;               ///< Array de balas
        std::vector<Cogible*>* cogibles;         ///< Array de cogibles
        std::vector<Muelle*>* muelles;           ///< Array de muelles
        std::vector<Teleport*>* teletransportes; ///< Array de teletransportes
        Pistola* pistola;                        ///< Pistola
        GameResource<Camera>   camara;
        GameResource<Teleport> m_teletransportes[MAX_NUM_TELEPORT];
        GameResource<Player>   m_Players[MAX_NUM_PLAYER];
        GameResource<Pistola>  m_Pistolas[MAX_NUM_PISTOLA];
        GameResource<Escopeta> m_Escopetas[MAX_NUM_GRANADA];
        GameResource<Granada>  m_Granadas[MAX_NUM_ESCOPETA];
        GameResource<Bala>     m_Balas[MAX_NUM_BALA];
        GameResource<Muelle>   m_Muelles[MAX_NUM_MUELLE];
};

#endif // PHYSICWORLD_H
