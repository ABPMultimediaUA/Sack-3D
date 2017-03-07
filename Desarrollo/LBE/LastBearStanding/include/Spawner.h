
#ifndef SPAWNER_H
#define SPAWNER_H

#include "GameObject.h"
#include <irrlicht.h>


class Cogible;
class Spawner:public GameObject {
    public:
        Spawner(int tipo, int modelo, b2Vec2 pos);
        ~Spawner();
        void coger(Cogible* obj);
        void soltar();
        void actualiza();
        void generar();
        Cogible* getCogido(){return objCogido;}
    private:
        irr::f32 time;
        irr::ITimer* timer;
        b2RevoluteJoint* joint;
        Cogible* objCogido;
        bool cogiendo;
        int cadencia;
        int tipo;
        int modelo;
};

#endif // SPAWNER_H

