#ifndef MASTER_H
#define MASTER_H

#include "World.h"
#include "IrrManager.h"


struct Num2Map {
     int num;
     irr::core::stringw map;
};

class Master{
    public:
        Master();
        void Update();
        bool Run();
        void Drop();
        void InstanciaMundo();
        virtual ~Master(){}
    private:
    	bool finPartida = false;
        irr::f32 timeFPS;
        irr::ITimer* timerFPS;
    	irr::f32 timeFinPartida;
        irr::ITimer* timerFinPartida;
        const Num2Map maps[10] = {
              {  1         , irr::core::stringw("media/map1.tmx") }
            , {  2         , irr::core::stringw("media/map2.tmx") }
            , {  0         , irr::core::stringw("0")              }
        };
};

#endif // MASTER_H
