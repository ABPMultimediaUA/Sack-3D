#ifndef HUD_H
#define HUD_H

#include "BearManager.h"

class HUD{
    public:
        HUD(int*, int width,int height);
        ~HUD(){}
        void DrawHud(int marcador, int angle, int x, int y, int marginX, int marginY, irr::video::ITexture* texture);
        void Draw();

    private:
        BearMngr* m_BearMngr;
        irr::video::ITexture* m_hudImage_Red;
        irr::video::ITexture* m_hudImage_Green;
        irr::video::ITexture* m_hudImage_Yellow;
        irr::video::ITexture* m_hudImage_Pink;
        irr::gui::IGUIFont* font;
        irr::video::SColor fColor;
        irr::video::SColor black_color;
        int* puntuaciones;
        int m_width;
        int m_height;
};

#endif
