
#ifndef MAP_H
#define MAP_H

#include <irrlicht.h>

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
    private:
    	const Layer2Method layers[8] = {
              { L"Spawners"       , AddSpawner    }
            , { L"Colisiones"     , AddPlatform   }
            , { L"Muelles"        , AddMuelle     }
            , { L"Teleports"      , AddTeleport   }
            , { L"Armas"          , AddArma       }
            , { L"Players"        , AddPlayer     }
            , { L"Pinchos"        , AddPincho     }
            , { L"0"              , 0             }
        };
        int x;
        int y;
        int width;
        int height;
        int name;
        int type;
        int player;
};

#endif
