#ifndef MAP_H
#define MAP_H

#include "World.h"
#include <sstream>
#include <tinyxml/tinyxml2.h>

class Lista;
class Map;
struct Layer2Method {
    const char* layer;
    void (Map::*p)();
};

class Map{
    public:
        Map(const char* doc);
        virtual ~Map(){}
        void AddSpawner();
		void AddPlatform();
		void AddMuelle();
		void AddTeleport();
		void AddArma();
		void AddPlayer();
		void AddPincho();
        void AddNodo();
        int getTime();
        Lista* getListaNodos();
        void leerElement(tinyxml2::XMLElement *element);
        void leerObjGroup(const char* layer, tinyxml2::XMLElement *objgroup);
    private:
    	const Layer2Method layers[9] = {
              { "Spawners"       , AddSpawner    }
            , { "Colisiones"     , AddPlatform   }
            , { "Muelles"        , AddMuelle     }
            , { "Teleports"      , AddTeleport   }
            , { "Armas"          , AddArma       }
            , { "Players"        , AddPlayer     }
            , { "Pinchos"        , AddPincho     }
            , { "Nodos"          , AddNodo       }
            , { "0"              , 0             }
        };
        float x;
        float y;
        b2Vec2 posi;
        int m_id;
        float width;
        float height;
        int name;
        int typeInt;
        const char* typeString;
        bool player;
        int numPlayer;
        int playerRed;
        GameResource<Lista> nodos;

        uint32 timeEspera;
};

#endif
