
#ifndef PHYSICWORLD_H
#define PHYSICWORLD_H
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
#include "PlayerRed.h"
#include "Client.h"
#define MAX_NUM_TELEPORT       10
#define MAX_NUM_PLAYER         4
#define MAX_NUM_PISTOLA        20
#define MAX_NUM_ESCOPETA       20
#define MAX_NUM_GRANADA        20
#define MAX_NUM_BALA           200
#define MAX_NUM_MUELLE         20

extern Client* cliente;

class PhysicWorld{
    public:
        static PhysicWorld* Instance();
        PhysicWorld();
        virtual ~PhysicWorld(){}
        void inicializaVariables();
        b2Body* CreateBox(int x,int y);
        void creaCuboMierda(int x, int y);
        b2World* GetWorld(){return world.Get();}
        Player* getPlayer(int);
        std::vector<Cogible*>*  GetCogibles(){         return cogibles;         }
        std::vector<PlayerRed*>* GetPlayersRed(){      return playersRed;       }
        GameResource<Player>*   GetPlayers(){          return m_Players;        }
        GameResource<Teleport>* GetTeletransportes(){  return m_Teletransportes;}
        GameResource<Muelle>*   GetMuelles(){          return m_Muelles;        }
        void setCogibles(std::vector<Cogible*>* aux){cogibles = aux;}
        void Update();



        GameResource<Teleport>* CreateTeleport(Teleport *tp = NULL){
            for (int i = 0; i < MAX_NUM_TELEPORT; ++i){
                if(m_Teletransportes[i].Get()== NULL){
                    m_Teletransportes[i].Reset(tp);
                    return &m_Teletransportes[i];
                }
            }
        }
        GameResource<Muelle>* CreateMuelle(Muelle *tp = NULL){
            for (int i = 0; i < MAX_NUM_MUELLE; ++i){
                if(m_Muelles[i].Get()== NULL){
                    m_Muelles[i].Reset(tp);
                    return &m_Muelles[i];
                }
            }
        }
        GameResource<Pistola>* CreatePistola(Pistola *tp = NULL){
            for (int i = 0; i < MAX_NUM_PISTOLA; ++i){
                if(m_Pistolas[i].Get()== NULL){
                    m_Pistolas[i].Reset(tp);
                    return &m_Pistolas[i];
                }
            }
        }
        GameResource<Escopeta>* CreateEscopeta(Escopeta *tp = NULL){
            for (int i = 0; i < MAX_NUM_ESCOPETA; ++i){
                if(m_Escopetas[i].Get()== NULL){
                    m_Escopetas[i].Reset(tp);
                    return &m_Escopetas[i];
                }
            }
        }
        GameResource<Granada>* CreateGranada(Granada *tp = NULL){
            for (int i = 0; i < MAX_NUM_GRANADA; ++i){
                if(m_Granadas[i].Get()== NULL){
                    m_Granadas[i].Reset(tp);
                    return &m_Granadas[i];
                }
            }
        }
        GameResource<Bala>* CreateBala(Bala *tp = NULL){
            for (int i = 0; i < MAX_NUM_BALA; ++i){
                if(m_Balas[i].Get()== NULL){
                    m_Balas[i].Reset(tp);
                    return &m_Balas[i];
                }
            }
        }
        GameResource<Player>* CreatePlayer(Player *tp = NULL){
            for (int i = 0; i < MAX_NUM_PLAYER; ++i){
                if(m_Players[i].Get()== NULL){
                    m_Players[i].Reset(tp);
                    return &m_Players[i];
                }
            }
        }
        b2RevoluteJoint* joint;
    private:
        static PhysicWorld* pinstance;
        GameResource<b2World> world;
        MyContactListener* contactListener;
        std::vector<Bala*>* balas;
        std::vector<Cogible*>* cogibles;
        std::vector<Muelle*>* muelles;
        std::vector<Teleport*>* teletransportes;
        std::vector<PlayerRed*>* playersRed;
        Pistola* pistola;
        float DeltaTime;
        float TimeStamp;
        GameResource<Camera>   camara;
        GameResource<Teleport> m_Teletransportes[MAX_NUM_TELEPORT];
        GameResource<Player>   m_Players[MAX_NUM_PLAYER];
        GameResource<Pistola>  m_Pistolas[MAX_NUM_PISTOLA];
        GameResource<Escopeta> m_Escopetas[MAX_NUM_GRANADA];
        GameResource<Granada>  m_Granadas[MAX_NUM_ESCOPETA];
        GameResource<Bala>     m_Balas[MAX_NUM_BALA];
        GameResource<Muelle>   m_Muelles[MAX_NUM_MUELLE];
};

#endif
