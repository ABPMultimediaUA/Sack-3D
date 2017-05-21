#ifndef MASTER_H
#define MASTER_H

#include <vector>
#include "Box2D/Box2D.h"
#include "FinPartida.h"
#include "MyEventReceiver.h"

class Menu;
class TMotorBear;
struct Num2Map {
     int num;
     const char* map;
};

class Master{
    public:
        Master();
        void Update();
        void UpdateGame();
        void UpdateMenu();
        void UpdateFinPartida();
        bool Run();
        void InstanciaMundo();
        virtual ~Master(){}
    private:
        MyEventReceiver eventReceiver;
        std::vector<int> mapList;
    	bool finPartida;
    	bool primeraInicializacion;
        uint32 timeFPS;
    	uint32 timeFinPartida;
        uint32 time2SyncClient;
        int puntuaciones[4];
        int m_game;
        int estado;
        Menu* menu;
        FinPartida* finPartidaObject;
        const Num2Map maps[11] = {
              {  1         , "media/Maps/MapFinding0.tmx" }
            , {  2         , "media/Maps/MapFinding9.tmx" }
            , {  3         , "media/Maps/MapFinding8.tmx" }
            , {  4         , "media/Maps/MapFinding7.tmx" }
            , {  5         , "media/Maps/MapFinding6.tmx" }
            , {  6         , "media/Maps/MapFinding5.tmx" }
            , {  7         , "media/Maps/MapFinding4.tmx" }
            , {  8         , "media/Maps/MapFinding3.tmx" }
            , {  9         , "media/Maps/MapFinding2.tmx" }
            , {  10        , "media/Maps/MapFinding1.tmx" }
            , {  11        , "0"                         }
        };
};

#endif // MASTER_H
