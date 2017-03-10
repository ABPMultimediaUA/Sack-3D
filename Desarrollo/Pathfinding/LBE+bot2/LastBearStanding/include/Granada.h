
#ifndef GRANADA_H
#define GRANADA_H

#include "Usable.h"

#define PARTICULAS 10

class Granada:public Usable{
    public:
        Granada(Spawner* expo, int modelo,b2Vec2 pos);
        virtual ~Granada();
        void actualiza();           
        void usar();                
    private:
        unsigned int timerGranada; 
        irr::ITimer* timerIrr;      
        b2Body* particulas[PARTICULAS];
        int mecha;
        bool usada;
        bool explotada;
};

#endif 