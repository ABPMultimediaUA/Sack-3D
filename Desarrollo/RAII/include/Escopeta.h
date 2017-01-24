#ifndef ESCOPETA_H
#define ESCOPETA_H

#include "Usable.h"

class Escopeta: public Usable{
    public:
        Escopeta(int modelo,b2Vec2 pos);
        virtual ~Escopeta();	
        void usar();                      
        bool getConUsos();                
        bool getTimerEscopeta();                
        bool getTimerIrr();                
    private:
        irr::f32 timerEscopeta;           
        irr::ITimer* timerIrr;            
	    int cadencia = 1000;
	    int usos = 4;
	    bool conUsos = true;;
};

#endif // ESCOPETA_H
