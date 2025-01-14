#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <Box2D/Box2D.h>
#include "GameResource.h"
#include "RVector.h"
#include "Client.h"


class Teleport;
class Player;
class Muelle;
class Cogible;
class Camera;
class Bala;
class Spawner;
class Platform;
class PlayerRed;
class DebugInfo;
class MyContactListener;
class Nodo;
class Lista;
class Map;
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
        void inicializaVariables(irr::core::stringw mapFile,int* puntuaciones);
        b2Body* CreateBox(int x,int y);
        void creaCuboMierda(int x, int y);
        b2World* GetWorld(){return world.Get();}
        Player* getPlayer(int);
        int getGanador();
        Lista* getListaNodos();
        void Reset();
        int Update(int fps);
        std::vector<Cogible*>   GetCogibles(){  return m_Cogibles.Get(); }
        std::vector<Bala*>      GetBalas(){     return m_Balas.Get();    }
        std::vector<Player*>    GetPlayers(){   return m_Players.Get();  }
        std::vector<Teleport*>  GetTeleports(){ return m_Teleports.Get();}
        std::vector<Muelle*>    GetMuelles(){   return m_Muelles.Get();  }
        std::vector<Spawner*>   GetSpawners(){  return m_Spawners.Get(); }
        std::vector<Platform*>  GetPlatforms(){ return m_Platforms.Get();}
        Cogible*  AddCogible (Cogible *x ) {m_Cogibles.Add(x); return x;}
        Bala*     AddBala    (Bala *x    )    {m_Balas.Add(x);    return x;}
        Teleport* AddTeleport(Teleport *x){m_Teleports.Add(x);return x;}
        Muelle*   AddMuelle  (Muelle *x  )  {m_Muelles.Add(x);  return x;}
        Player*   AddPlayer  (Player *x  )  {m_Players.Add(x);  return x;}
        Spawner*  AddSpawner (Spawner *x ) {m_Spawners.Add(x); return x;}
        Platform* AddPlatform(Platform *x){m_Platforms.Add(x);return x;}
        Nodo*     AddNodo    (Nodo *x)        {m_Nodos.Add(x);return x;}
        b2RevoluteJoint* joint;
    private:
        static World* pinstance;
        GameResource<b2World> world;
        GameResource<MyContactListener> contactListener;
        float DeltaTime;
        float TimeStamp;
        GameResource<Camera>   m_Camara;
        GameResource<Map>      m_Mapa;
        RVector<Teleport>      m_Teleports;
        RVector<Player>        m_Players;
        RVector<Muelle>        m_Muelles;
        RVector<Cogible>       m_Cogibles;
        RVector<Bala>          m_Balas;
        RVector<Spawner>       m_Spawners;
        RVector<Platform>      m_Platforms;
        RVector<Nodo>          m_Nodos;
};

#endif
