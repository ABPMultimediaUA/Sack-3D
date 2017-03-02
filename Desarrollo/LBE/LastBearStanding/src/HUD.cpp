#include "HUD.h"
#include "World.h"

HUD::HUD(int* puntuaciones):puntuaciones(puntuaciones){
    font = IrrMngr::Inst()->getGUI()->getFont("media/Fuentes/hud.bmp");
	fColor = irr::video::SColor(150,0, 0,0);
}
void HUD::Draw(){
	//IrrMngr::Inst()->getDriver()->draw2DRectangle(irr::video::SColor(150,0, 150,0)  ,irr::core::rect<irr::s32>(150,40,300,70));
	//IrrMngr::Inst()->getDriver()->draw2DRectangle(irr::video::SColor(150,0, 0,150)  ,irr::core::rect<irr::s32>(250,40,400,70));
	//IrrMngr::Inst()->getDriver()->draw2DRectangle(irr::video::SColor(150,150, 0,150),irr::core::rect<irr::s32>(350,40,500,70));
	int posx = 100;
	for (int i = 0; i < 4; ++i){
		irr::video::SColor color;
		switch(i){
			case 0: color = irr::video::SColor(150,150, 0,0)  ; break;
			case 1: color = irr::video::SColor(150,0, 150,0)  ; break;
			case 2: color = irr::video::SColor(150,0, 0,150)  ; break;
			case 3: color = irr::video::SColor(150,150, 0,150); break;
		}
		IrrMngr::Inst()->getDriver()->draw2DRectangle(color  ,irr::core::rect<irr::s32>(posx-7, 37,posx+56,100));
		font->draw(irr::core::stringw(puntuaciones[i]),irr::core::rect<irr::s32>(posx, 20,50,50),fColor);
		posx += 100;
	}
}
