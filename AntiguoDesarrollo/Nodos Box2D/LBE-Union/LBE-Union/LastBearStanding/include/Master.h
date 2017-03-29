#ifndef MASTER_1
#define MASTER_H

#include <irrlicht.h>
#include <vector>

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
        std::vector<int> mapList;
    	bool finPartida;
        irr::f32 timeFPS;
        irr::ITimer* timerFPS;
    	irr::f32 timeFinPartida;
        irr::ITimer* timerFinPartida;
        irr::f32 time2SyncClient;
        int puntuaciones[4];
        int game;
        const Num2Map maps[7] = {
              {  1         , L"media/Maps/MapFinding1.tmx" }
            , {  2         , L"media/Maps/MapFinding1.tmx" }
            , {  3         , L"media/Maps/MapFinding1.tmx" }
            , {  4         , L"media/Maps/MapFinding1.tmx" }
            , {  5         , L"media/Maps/MapFinding1.tmx" }
            , {  6         , L"media/Maps/MapFinding1.tmx" }
            , {  0         , L"0"                          }
        };
};

#endif // MASTER_H
