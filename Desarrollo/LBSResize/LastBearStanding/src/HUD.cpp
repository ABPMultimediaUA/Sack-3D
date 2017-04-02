#include "HUD.h"
#include "World.h"

HUD::HUD(int* puntuaciones, int width,int height):puntuaciones(puntuaciones),width(width),height(height){
    font = IrrMngr::Inst()->getGUI()->getFont("media/Fuentes/hud.bmp");
	fColor = irr::video::SColor(150,0, 0,0);
}
void HUD::Draw(){
	int posx = (width/2)-180;
	for (int i = 0; i < 4; ++i){
		irr::video::SColor color;
		switch(i){
			case 0: color = irr::video::SColor(255,255, 0,0)  ; break;
			case 1: color = irr::video::SColor(255,0, 255,0)  ; break;
			case 2: color = irr::video::SColor(255,0, 0,255)  ; break;
			case 3: color = irr::video::SColor(255,255, 0,255); break;
		}
		IrrMngr::Inst()->getDriver()->draw2DRectangle(color  ,irr::core::rect<irr::s32>(posx-7, 37,posx+56,100));
		font->draw(irr::core::stringw(puntuaciones[i]),irr::core::rect<irr::s32>(posx, 20,50,50),fColor);
		posx += 100;
	}
}
