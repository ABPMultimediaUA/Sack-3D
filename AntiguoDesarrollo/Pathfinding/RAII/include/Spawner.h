/*
#ifndef SPAWNER_H
#define SPAWNER_H

#include "Cogible.h"
#include "Bala.h"
#include "IrrManager.h"

class Spawner {
    public:
        Spawner(int tipo, int modelo, irr::core::vector3df pos);
        ~Spawner(){}
        void coger(Cogible* obj);
        Cogible* getCogido();
        void soltar();
        void actualiza();
        void generar();
    private:
        int time;
        irr::ITimer* timer;
        b2Body* body;
        b2RevoluteJoint* joint;
        Cogible* objCogido;
        bool cogiendo = true;
        int tipo;
        int modelo;
};

#endif // SPAWNER_H
*/
