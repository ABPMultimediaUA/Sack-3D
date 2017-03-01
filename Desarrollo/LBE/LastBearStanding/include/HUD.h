#ifndef HUD_H
#define HUD_H

#include "IrrManager.h"

class HUD{
    public:
        HUD(int*);
        virtual ~HUD(){}
        void Draw();

    private:
        irr::gui::IGUIFont* font;
        irr::video::SColor fColor;
        int* puntuaciones;
};

#endif