#include "HUD.h"
#include "World.h"

HUD::HUD(int* puntuaciones, int width,int height):puntuaciones(puntuaciones),m_width(width),m_height(height){
    m_BearMngr = BearMngr::Inst();
    font = BearMngr::Inst()->getGUI()->getFont("media/Fuentes/hud.bmp");
	fColor = irr::video::SColor(150,0, 0,0);
	irr::video::SColor color(255,255, 255,255);
	black_color = irr::video::SColor(255,0, 0,0);
	m_hudImage_Red = m_BearMngr->getDriver()->getTexture("media/Images/Hud/hud_Red.png");
	m_hudImage_Green = m_BearMngr->getDriver()->getTexture("media/Images/Hud/hud_Green.png");
	m_hudImage_Pink = m_BearMngr->getDriver()->getTexture("media/Images/Hud/hud_Pink.png");
	m_hudImage_Yellow = m_BearMngr->getDriver()->getTexture("media/Images/Hud/hud_Yellow.png");
    m_BearMngr->getDriver()->makeColorKeyTexture(m_hudImage_Red,    color);
    m_BearMngr->getDriver()->makeColorKeyTexture(m_hudImage_Green,  color);
    m_BearMngr->getDriver()->makeColorKeyTexture(m_hudImage_Pink,   color);
    m_BearMngr->getDriver()->makeColorKeyTexture(m_hudImage_Yellow, color);
}
void HUD::Draw(){
	int increment = m_width/6;
	int pos       = m_width/2-(increment*1.4f);
	int posY = m_height;
	DrawHud(0, 10,  pos,               posY,  24, -7, m_hudImage_Green );
	DrawHud(1, 180, pos+increment,	   posY , 35, -6, m_hudImage_Yellow);
	DrawHud(2, 30,  pos+(increment*2), posY , 22, -7, m_hudImage_Red   );
	DrawHud(3, 45,  pos+(increment*3), posY,  28, -10, m_hudImage_Pink  );
}

void HUD::DrawHud(int marcador, int angle, int x, int y, int marginX, int marginY, irr::video::ITexture* texture){

	int width  = texture->getSize().Width;
	int height = texture->getSize().Height;

	int posX = x-(width/2);
	int posY = y-(height/2);


	irr::core::rect<irr::s32> position ( posX, posY, posX+(width*3/5),  posY+(height*3/5));
	irr::core::rect<irr::s32> imageRect( 0, 0, width  ,  height  );

    m_BearMngr->getDriver()->draw2DImage(texture,position,imageRect,NULL,NULL,true);
	font->draw(irr::core::stringw(puntuaciones[marcador]),irr::core::rect<irr::s32>(posX+marginX,posY+marginY,20,50),black_color);
}
