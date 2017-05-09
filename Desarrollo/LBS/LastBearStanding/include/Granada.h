
#ifndef GRANADA_H
#define GRANADA_H

#include "Usable.h"

#define PARTICULAS 25

class Granada:public Usable{
    public:
        Granada(Spawner* expo, int modelo,b2Vec2 pos);
        ~Granada();
        void actualiza();
        void setCogido(bool aux);
        void setCogedor(int aux);
        void Explosion();
        void usar();
    private:
        unsigned int timerGranada;
        irr::ITimer* timerIrr;
        b2Body* particulas[PARTICULAS];
        int mecha;
        int cogedor;
        bool usada;
};

#endif
