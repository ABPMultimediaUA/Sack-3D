#include "HUD.h"
#include "World.h"

HUD::HUD(int* puntuaciones):puntuaciones(puntuaciones){
    font = IrrMngr::Inst()->getGUI()->getFont("media/Fuentes/hud.bmp");
	fColor = irr::video::SColor(150,0, 0,0);
}
void HUD::Draw(){
	for (int i = 0; i < 4; ++i){
		IrrMngr::Inst()->getDriver()->draw2DRectangle(irr::video::SColor(150,150, 0,0)  ,irr::core::rect<irr::s32>(50, 40,200,70));
	}
	//IrrMngr::Inst()->getDriver()->draw2DRectangle(irr::video::SColor(150,0, 150,0)  ,irr::core::rect<irr::s32>(150,40,300,70));
	//IrrMngr::Inst()->getDriver()->draw2DRectangle(irr::video::SColor(150,0, 0,150)  ,irr::core::rect<irr::s32>(250,40,400,70));
	//IrrMngr::Inst()->getDriver()->draw2DRectangle(irr::video::SColor(150,150, 0,150),irr::core::rect<irr::s32>(350,40,500,70));
	int posx = 100;
	for (int i = 0; i < 4; ++i){
		font->draw(irr::core::stringw(puntuaciones[i]),irr::core::rect<irr::s32>(posx, 20,50,50),fColor);
		posx += 100;
	}
}
