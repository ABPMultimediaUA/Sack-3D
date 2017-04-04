#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H

#include "World.h"

class MyContactListener;
class Player;
class Cogible;
class Muelle;
class Teleport;
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
        void PlayerNodo();
        void TeleportBala();
        void TeleportCogible();
        void PiesPlayerBegin();
        void PiesPlayerEnd();
        void BalaBegin();
    private:
    	const static Contact2Method beginContact[11];
        const static Contact2Method endContact[3];
        World* m_pWorld;
        b2Contact* contact;
        Player* GetPlayer();
        Cogible* GetCogible();
        Muelle* GetMuelle();
        Teleport* GetTeleport();
        Bala* GetBala();
        Nodo* GetNodo();
};

#endif
