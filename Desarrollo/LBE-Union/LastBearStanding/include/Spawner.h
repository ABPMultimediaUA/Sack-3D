
#ifndef SPAWNER_H
#define SPAWNER_H

#include "GameObject.h"
#include <irrlicht.h>


class Cogible;
class IrrMngr;
class World;
class Spawner{
    public:
        Spawner(int tipo, int modelo, b2Vec2 pos);
        ~Spawner();
        void coger(Cogible *objCogido);
        void soltar();
        void actualiza();
        void generar();
        int GetId();
        Cogible* getCogido(){return objCogido;}
    private:
        IrrMngr *m_pIrrMngr;
        World *m_pWorld;
        GameObject m_gameObject;
        irr::f32 time;
        irr::ITimer* timer;
        Cogible* objCogido;
        bool cogiendo;
        int cadencia;
        int tipo;
        int modelo;
        int m_id;
};

#endif // SPAWNER_H

