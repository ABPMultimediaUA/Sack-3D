#ifndef MAP_H
#define MAP_H
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
class Map{
    public:
        Map(stringw file);
        virtual ~Map();
    protected:
    private:
};

#endif // MAP_H
