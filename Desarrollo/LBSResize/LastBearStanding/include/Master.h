#ifndef MASTER_H
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
        const static Num2Map maps[7];
};

#endif // MASTER_H
