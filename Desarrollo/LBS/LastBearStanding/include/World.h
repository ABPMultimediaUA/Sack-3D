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
class Nodo;
class Lista;
class Bala;
class Spawner;
class GameObject;
class Platform;
class PlayerRed;
class DebugInfo;
class Map;
class Metralla;
class Particle;
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
    M_SPAWNER        = 0x0100,
    M_NODO           = 0x0200,
    M_PARTICULA      = 0x0300,
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
    DATA_SPAWNER         = 10,
    DATA_NODO            = 11,
    DATA_PARTICULA       = 12,
};

class World{
    public:
        static World* Inst();
        World();
        virtual ~World(){}
        void inicializaVariables(irr::core::stringw mapFile,int* puntuaciones);
        b2World* GetWorld(){return world;}
        Player* getPlayer(int);
        void  SwitchDebugMode();
        Lista* getListaNodos();
        int getGanador();
        void Reset();
        int getVivos();
        int Update(int fps);
        void UpdateCogibles();
        void UpdateBalas();
        int  UpdatePlayers();
        void UpdateSpawners();
        void UpdateMetrallas();
        void UpdateParticles();
        std::vector<Cogible*>   GetCogibles();
        std::vector<Bala*>      GetBalas();
        std::vector<Player*>    GetPlayers();
        std::vector<Teleport*>  GetTeleports();
        std::vector<Muelle*>    GetMuelles();
        std::vector<Spawner*>   GetSpawners();
        std::vector<Platform*>  GetPlatforms();
        std::vector<Nodo*>      GetNodos();
        std::vector<Metralla*>  GetMetrallas();
        std::vector<Particle*>  GetParticles();
        Cogible*  AddCogible (Cogible *x );
        Bala*     AddBala    (Bala *x    );
        Teleport* AddTeleport(Teleport *x);
        Muelle*   AddMuelle  (Muelle *x  );
        Player*   AddPlayer  (Player *x  );
        Spawner*  AddSpawner (Spawner *x );
        Platform* AddPlatform(Platform *x);
        Nodo*     AddNodo    (Nodo *x)    ;
        Metralla* AddMetralla(Metralla *x);
        Particle* AddParticle(Particle *x);
        b2RevoluteJoint* joint;
        const static float Size;
    private:
        GameResource<MyContactListener> contactListener;
        static World*          pinstance;
        static const int       velocityIterations;
        static const int       positionIterations;
        b2World                *world;
        float                  DeltaTime;
        float                  TimeStamp;
        bool                   m_debugMode;
        GameResource<Camera>   camara;
        GameResource<Map>      m_Mapa;
        RVector<Teleport>      m_Teleports;
        RVector<Player>        m_Players;
        RVector<Muelle>        m_Muelles;
        RVector<Cogible>       m_Cogibles;
        RVector<Bala>          m_Balas;
        RVector<Spawner>       m_Spawners;
        RVector<Platform>      m_Platforms;
        RVector<Nodo>          m_Nodos;
        RVector<Metralla>      m_Metrallas;
        RVector<Particle>      m_Particles;
};

#endif
