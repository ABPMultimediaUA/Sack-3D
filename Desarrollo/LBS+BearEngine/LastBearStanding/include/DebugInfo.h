#ifndef DEBUGINFO_H
#define DEBUGINFO_H

#include "BearManager.h"
#include "World.h"

class DebugInfo{
    public:
        DebugInfo();
        virtual ~DebugInfo(){}
        void Draw(int fps);
    private:
        //irr::gui::IGUIFont* font;
        //irr::video::SColor fColor;
        //irr::video::SColor rectColor;
        //irr::core::rect<int> rect;
};

#endif // DEBUGINFO_H
