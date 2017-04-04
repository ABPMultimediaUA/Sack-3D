
#ifndef MAP_H
#define MAP_H

#include "World.h"
#include <sstream>
#include <irrlicht.h>

class Lista;
class Map;
struct Layer2Method {
    irr::core::stringw layer;
    void (Map::*p)();
};

class Map{
    public:
        Map(irr::core::stringw file);
        virtual ~Map(){}
        void AddSpawner();
		void AddPlatform();
		void AddMuelle();
		void AddTeleport();
		void AddArma();
		void AddPlayer();
		void AddPincho();
        void AddNodo();
        Lista* getListaNodos();
    private:
        int x;
        int y;
        b2Vec2 posi;
        const static Layer2Method layers[10];
        int m_id;
        int width;
        int height;
        int name;
        int typeInt;
        std::wstring typeString;
        bool player;
        int numPlayer;
        int playerRed;
        GameResource<Lista> nodos;
};

#endif
