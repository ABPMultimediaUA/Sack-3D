#ifndef MASTER_H
#define MASTER_H

#include <vector>
#include "Box2D/Box2D.h"
#include "MyEventReceiver.h"

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
        MyEventReceiver eventReceiver;
        std::vector<int> mapList;
    	bool finPartida;
        uint32 timeFPS;
    	uint32 timeFinPartida;
        uint32 time2SyncClient;
        int puntuaciones[4];
        int m_game;
        const Num2Map maps[7] = {
              {  1         , "media/Maps/MapFinding1.tmx" }
            , {  2         , "media/Maps/MapFinding1.tmx" }
            , {  4         , "media/Maps/MapFinding1.tmx" }
            , {  5         , "media/Maps/MapFinding1.tmx" }
            , {  6         , "media/Maps/MapFinding1.tmx" }
            , {  3         , "media/Maps/MapFinding1.tmx" }
            , {  0         , "0"                          }
        };
};

#endif // MASTER_H
