#ifndef MASTER_H
#define MASTER_H

#include "World.h"
#include "IrrManager.h"

class Master{
    public:
        Master();
        void Update();
        bool Run();
        void Drop();
        virtual ~Master(){}
    private:
    	bool finPartida = false;
    	irr::f32 timeFinPartida;
        irr::ITimer* timerFinPartida;
};

#endif // MASTER_H
