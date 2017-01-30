
#ifndef GRANADA_H
#define GRANADA_H

#include <vector>
#include "Usable.h"

#define PARTICULAS 10

class Granada:public Usable{
    public:
        Granada(int modelo,b2Vec2 pos);
        virtual ~Granada(){}
        void actualiza();           
        void usar();                
    private:
        irr::f32 timerGranada; 
        irr::ITimer* timerIrr;      
        b2Body* particulas[PARTICULAS];
        int mecha = 4000;
        bool usada = false;
};

#endif // GRANADA_H
