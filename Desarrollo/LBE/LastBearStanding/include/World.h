
#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <Box2D/Box2D.h>
#include <iostream>
#include "Player.h"
#include "Pistola.h"
#include "Escopeta.h"
#include "Granada.h"
#include "Bala.h"
#include "Muelle.h"
#include "Teleport.h"
#include "Spawner.h"
#include "PlayerRed.h"
#include "Platform.h"
#include "GameResource.h"
#include "RVector.h"
#include <vector>
#include "Map.h"
#include "Camera.h"
#include "Client.h"

extern Client* cliente;

class MyContactListener;
enum MascaraColisiones {
    M_PLAYER         = 0x0001,
    M_SUELO          = 0x0002,
    M_COGIBLE        = 0x0004,
    M_BALA           = 0x0008,
    M_TELEPORT       = 0x0010,
    M_MUELLE         = 0x0020,
    M_COGIBLESENSOR  = 0x0040,
    M_PINCHO         = 0x0080,
};

enum UserDatas {
    DATA_PLAYER          = 1,
    DATA_PLAYER_PIES     = 2,
    DATA_COGIBLE         = 3,
    DATA_COGIBLE_SENSOR  = 4,
    DATA_BALA            = 5,
    DATA_TELEPORT        = 6,
    DATA_MUELLE          = 7,
    DATA_SUELO           = 8,
    DATA_PINCHO          = 9,
};


class World{
    public:
        static World* Inst();
        World();
        virtual ~World(){}
        void inicializaVariables(irr::core::stringw mapFile);
        b2Body* CreateBox(int x,int y);
        void creaCuboMierda(int x, int y);
        b2World* GetWorld(){return world.Get();}
        Player* getPlayer(int);
        void Reset();
        int Update();
        std::vector<Cogible*>  GetCogibles(){  return m_Cogibles.Get(); }
        std::vector<Bala*>     GetBalas(){     return m_Balas.Get();    }
        std::vector<Player*>   GetPlayers(){   return m_Players.Get();  }
        std::vector<Teleport*> GetTeleports(){ return m_Teleports.Get();}
        std::vector<Muelle*>   GetMuelles(){   return m_Muelles.Get();  }
        std::vector<Spawner*>  GetSpawners(){  return m_Spawners.Get(); }
        std::vector<Platform*> GetPlatforms(){ return m_Platforms.Get();}
        std::vector<PlayerRed*> GetPlayersRed(){ return m_PlayersRed.Get();}
        Cogible*  AddCogible (Cogible *x = NULL) {m_Cogibles.Add(x); return x;}
        Bala*     AddBala    (Bala *x = NULL)    {m_Balas.Add(x);    return x;}
        Teleport* AddTeleport(Teleport *x = NULL){m_Teleports.Add(x);return x;}
        Muelle*   AddMuelle  (Muelle *x = NULL)  {m_Muelles.Add(x);  return x;}
        Player*   AddPlayer  (Player *x = NULL)  {m_Players.Add(x);  return x;}
        Spawner*  AddSpawner (Spawner *x = NULL) {m_Spawners.Add(x); return x;}
        Platform* AddPlatform(Platform *x = NULL){m_Platforms.Add(x);return x;}
        PlayerRed* AddPlayerRed(PlayerRed *x = NULL){m_PlayersRed.Add(x);return x;}
        b2RevoluteJoint* joint;
    private:
        static World* pinstance;
        GameResource<b2World> world;
        GameResource<MyContactListener> contactListener;
        float DeltaTime;
        float TimeStamp;
        GameResource<Camera>   camara;
        RVector<Teleport>      m_Teleports;
        RVector<Player>        m_Players;
        RVector<Muelle>        m_Muelles;
        RVector<Cogible>       m_Cogibles;
        RVector<Bala>          m_Balas;
        RVector<Spawner>       m_Spawners;
        RVector<Platform>      m_Platforms;
        RVector<PlayerRed>     m_PlayersRed;
};

#endif
