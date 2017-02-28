#ifndef ESCOPETA_H
#define ESCOPETA_H

#include "Usable.h"

class Escopeta: public Usable{
    public:
        Escopeta(int modelo,b2Vec2 pos);
        virtual ~Escopeta(){}	
        void usar();                      
    private:
        irr::f32 timerEscopeta;           
        irr::ITimer* timerIrr;            
	    int cadencia = 10;
	    int usos = 400;
	    bool conUsos = true;;
};

#endif 