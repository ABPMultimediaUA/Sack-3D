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
        const Num2Map maps[7] = {
              {  1         , L"media/Maps/MapFinding1.tmx" }
            , {  2         , L"media/Maps/MapFinding2.tmx" }
            , {  3         , L"media/Maps/MapFinding3.tmx" }
            , {  4         , L"media/Maps/MapFinding4.tmx" }
            , {  5         , L"media/Maps/MapFinding5.tmx" }
            , {  6         , L"media/Maps/MapFinding6.tmx" }
            , {  0         , L"0"                          }
        };
};

#endif // MASTER_H
