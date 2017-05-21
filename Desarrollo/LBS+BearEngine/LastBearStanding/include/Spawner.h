
#ifndef SPAWNER_H
#define SPAWNER_H

#include "GameObject.h"


class Cogible;
class BearMngr;
class World;
class Spawner{
    public:
        Spawner(int tipo, int modelo, b2Vec2 pos, int idc);
        ~Spawner();
        void coger(Cogible *objCogido);
        void soltar();
        void actualiza();
        void generar();
        int GetId();
        void ParticleSpawn();
        b2Vec2 GetPosition();
        Cogible* getCogido(){return objCogido;}
        bool GetCogiendo(){return cogiendo;}
    private:
        BearMngr *m_pBearMngr;
        World *m_pWorld;
        b2Vec2 m_pos;
        GameObject m_gameObject;
        uint32 time;
        Cogible* objCogido;
        bool cogiendo;
        int cadencia;
        int tipo;
        int modelo;
        int m_id;
        int id;
        int cont;
};

#endif // SPAWNER_H

