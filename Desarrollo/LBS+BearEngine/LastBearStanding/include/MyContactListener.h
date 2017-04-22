#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H

#include "World.h"

class MyContactListener;
class Player;
class Cogible;
class Muelle;
class Teleport;
class Mertalla;
class Bala;
struct Contact2Method {
     unsigned long A;
     unsigned long B;
     void (MyContactListener::*p)();
};

class MyContactListener: public b2ContactListener{
    public:
        MyContactListener();
        virtual ~MyContactListener(){}
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PlayerMuelle();
        void PlayerTeleport();
        void PlayerCogibleBegin();
        void PlayerCogibleEnd();
        void PlayerBala();
        void PlayerPincho();
        void PlayerMetralla();
        void PlayerNodo();
        void TeleportBala();
        void TeleportCogible();
        void PiesPlayerBegin();
        void PiesPlayerEnd();
        void BalaBegin();
    private:
        const Contact2Method beginContact[12] = {
              { DATA_PLAYER         , DATA_MUELLE         , PlayerMuelle        }
            , { DATA_PLAYER         , DATA_TELEPORT       , PlayerTeleport      }
            , { DATA_PLAYER         , DATA_COGIBLE_SENSOR , PlayerCogibleBegin  }
            , { DATA_PLAYER         , DATA_BALA           , PlayerBala          }
            , { DATA_PLAYER         , DATA_PINCHO         , PlayerPincho        }
            , { DATA_PLAYER         , DATA_NODO           , PlayerNodo          }
            , { DATA_PLAYER         , DATA_METRALLA       , PlayerMetralla      }
            , { DATA_TELEPORT       , DATA_BALA           , TeleportBala        }
            , { DATA_TELEPORT       , DATA_COGIBLE        , TeleportCogible     }
            , { DATA_PLAYER_PIES    , 0                   , PiesPlayerBegin     }
            , { DATA_BALA           , 0                   , BalaBegin           }
            , { 0                   , 0                   , 0                   }
        };
        const Contact2Method endContact[3] = {
              { DATA_PLAYER         , DATA_COGIBLE_SENSOR , PlayerCogibleEnd    }
            , { DATA_PLAYER_PIES    , 0                   , PiesPlayerEnd       }
            , { 0                   , 0                   , 0                   }
        };
        World* m_pWorld;
        b2Contact* contact;
        Player* GetPlayer();
        Cogible* GetCogible();
        Muelle* GetMuelle();
        Teleport* GetTeleport();
        Bala* GetBala();
        Nodo* GetNodo();
        Metralla* GetMetralla();
};

#endif
