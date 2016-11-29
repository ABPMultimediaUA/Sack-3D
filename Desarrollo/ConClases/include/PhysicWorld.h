#ifndef PHYSICWORLD_H
#define PHYSICWORLD_H
#include <Box2D/Box2D.h>
#include <iostream>
#include "PhysicWorld.h"
#include "cuboMierda.h"
#include "Player.h"

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
        b2Body* CreateBox(int x,int y);
        void Step(float DeltaTime);
        void ClearForces();
        void setPlayer(Player* jugador);
        Player* getPlayer();
        virtual ~PhysicWorld();

    private:
        static PhysicWorld* pinstance;
        b2World* world;
        std::vector<cuboMierda*>* cubos;
        Player* jugador1 = 0;
};

#endif // PHYSICWORLD_H
