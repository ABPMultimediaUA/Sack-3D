#ifndef MASTER_H
#define MASTER_H

#include <irrlicht.h>

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
    	bool finPartida;
        irr::f32 timeFPS;
        irr::ITimer* timerFPS;
    	irr::f32 timeFinPartida;
        irr::ITimer* timerFinPartida;
        irr::f32 time2SyncClient;
        int puntuaciones[4];
        const Num2Map maps[3] = {
              {  1         , L"media/Maps/Map1.tmx" }
            , {  2         , L"media/Maps/Map1.tmx" }
            , {  0         , L"0"                   }
        };
};

#endif // MASTER_H
