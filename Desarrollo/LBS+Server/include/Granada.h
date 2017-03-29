
#ifndef GRANADA_H
#define GRANADA_H

#include "Usable.h"

#define PARTICULAS 10

class Granada:public Usable{
    public:
        Granada(Spawner* expo, int modelo,b2Vec2 pos);
        ~Granada();
        void actualiza();           
        void setCogido(bool aux);
        void usar();                
    private:
        unsigned int timerGranada; 
        irr::ITimer* timerIrr;      
        b2Body* particulas[PARTICULAS];
        int mecha;
        bool usada;
};

#endif 