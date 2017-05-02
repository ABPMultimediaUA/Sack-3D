#ifndef MASTER_H
#define MASTER_H

#include <irrlicht.h>
#include <vector>
#include "Box2D/Box2D.h"

struct Num2Map {
     int num;
     const char* map;
};

class Master{
    public:
        Master();
        void Update();
        bool Run();
        void InstanciaMundo();
        virtual ~Master(){}
    private:
        std::vector<int> mapList;
    	bool finPartida;
        uint32 timeFPS;
    	uint32 timeFinPartida;
        uint32 time2SyncClient;
        int puntuaciones[4];
        int game;
        const Num2Map maps[7] = {
              {  1         , "media/Maps/MapFinding1.tmx" }
            , {  2         , "media/Maps/MapFinding2.tmx" }
            , {  4         , "media/Maps/MapFinding3.tmx" }
            , {  5         , "media/Maps/MapFinding4.tmx" }
            , {  6         , "media/Maps/MapFinding5.tmx" }
            , {  3         , "media/Maps/MapFinding6.tmx" }
            , {  0         , "0"                          }
        };
};

#endif // MASTER_H
