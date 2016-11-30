#ifndef PHYSICWORLD_H
#define PHYSICWORLD_H
#include <Box2D/Box2D.h>
#include <iostream>
#include "PhysicWorld.h"
#include "cuboMierda.h"
#include "Player.h"
#include "MyContactListener.h"
#include "Arma.h"
#include "Bala.h"

#include <vector>
#define VELITER 6              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 2              //NUMERO DE ITERACIONES POR TICK PARA CALCULAR LA POSICION
#define TIMESTEP 1.0f / 250.0f     //TIEMPO DE REFRESCO

class PhysicWorld{
    public:
    	static PhysicWorld* Instance();
        PhysicWorld();
        b2World* GetWorld();
        void creaCuboMierda(int x, int y);
        std::vector<cuboMierda*>* GetCubos();
        std::vector<Bala*>* GetBalas();
        b2Body* CreateBox(int x,int y);
        void Step(float DeltaTime);
        void ClearForces();
        void setPlayer(Player* jugador);
        void setArma(Arma* arma);
        Player* getPlayer();
        Arma* getArma();
        virtual ~PhysicWorld();



        b2RevoluteJoint* joint;

    private:
        static PhysicWorld* pinstance;
        b2World* world;
        MyContactListener* myContactListenerInstance;
        std::vector<cuboMierda*>* cubos;
        std::vector<Bala*>* balas;
        Player* jugador1 = 0;
        Arma* arma;
};

#endif // PHYSICWORLD_H
