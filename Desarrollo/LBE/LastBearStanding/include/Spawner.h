
#ifndef SPAWNER_H
#define SPAWNER_H

#include "Cogible.h"
#include "IrrManager.h"

class Spawner {
    public:
        Spawner(int tipo, int modelo, b2Vec2 pos);
        ~Spawner();
        void coger(Cogible* obj);
        void soltar();
        void actualiza();
        void generar();
        Cogible* getCogido(){return objCogido;}
    private:
        irr::scene::IMeshSceneNode* node; 
        irr::f32 time;
        irr::ITimer* timer;
        b2Vec2 pos;
        b2Body* body;
        b2RevoluteJoint* joint;
        Cogible* objCogido;
        bool cogiendo = true;
        int cadencia = 2000;
        int tipo;
        int modelo;
};

#endif // SPAWNER_H

