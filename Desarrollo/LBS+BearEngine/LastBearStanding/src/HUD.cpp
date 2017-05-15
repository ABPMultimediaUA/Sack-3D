#include "HUD.h"
#include "World.h"
#include "PhysicBody/PBDefault.h"

HUD::HUD(){}
HUD::Inicialize(int *puntuaciones){
	m_red.Inicialize(   new PBDefault(),0,0,0,b2Vec2(0,0),glm::vec3(0.4f ,0.2f ,0.001f),NULL,"media/Images/Hud/hud_Red.png", false);
	m_green.Inicialize( new PBDefault(),0,0,0,b2Vec2(0,0),glm::vec3(0.4f ,0.2f ,0.001f),NULL,"media/Images/Hud/hud_Green.png", false);
	m_yellow.Inicialize(new PBDefault(),0,0,0,b2Vec2(0,0),glm::vec3(0.4f ,0.2f ,0.001f),NULL,"media/Images/Hud/hud_Yellow.png", false);
	m_pink.Inicialize(  new PBDefault(),0,0,0,b2Vec2(0,0),glm::vec3(0.4f ,0.2f ,0.001f),NULL,"media/Images/Hud/hud_Pink.png", false);

    m_redPoints.Inicialize(   new PBDefault(),0,0,0,b2Vec2(0,0),glm::vec3(0.4f ,0.2f ,0.005f),NULL,contadores[puntuaciones[0]%6], false);
    m_greenPoints.Inicialize( new PBDefault(),0,0,0,b2Vec2(0,0),glm::vec3(0.4f ,0.2f ,0.005f),NULL,contadores[puntuaciones[1]%6], false);
    m_yellowPoints.Inicialize(new PBDefault(),0,0,0,b2Vec2(0,0),glm::vec3(0.4f ,0.2f ,0.005f),NULL,contadores[puntuaciones[2]%6], false);
    m_pinkPoints.Inicialize(  new PBDefault(),0,0,0,b2Vec2(0,0),glm::vec3(0.4f ,0.2f ,0.005f),NULL,contadores[puntuaciones[3]%6], false);

 	m_red.SetRotation(    -105 * 3.14 / 180);
 	m_green.SetRotation(  -95 * 3.14 / 180);
 	m_yellow.SetRotation( -85 * 3.14 / 180);
 	m_pink.SetRotation(   -78 * 3.14 / 180);

 	m_redPoints.SetRotation(    -105 * 3.14 / 180);
 	m_greenPoints.SetRotation(  -95 * 3.14 / 180);
 	m_yellowPoints.SetRotation( -85 * 3.14 / 180);
 	m_pinkPoints.SetRotation(   -78 * 3.14 / 180);

}
void HUD::Update(glm::vec3 pos){
	m_redPoints.SetPosition(    b2Vec2(pos.x - 1.2f    , pos.y - 1 ));
	m_greenPoints.SetPosition(  b2Vec2(pos.x - 0.4f    , pos.y - 1 ));
	m_yellowPoints.SetPosition( b2Vec2(pos.x + 0.4f    , pos.y - 1 ));
	m_pinkPoints.SetPosition(   b2Vec2(pos.x + 1.2f    , pos.y - 1 ));

	m_redPoints.SetZ(pos.z    - 2.58f );
	m_greenPoints.SetZ(pos.z  - 2.58f );
	m_yellowPoints.SetZ(pos.z - 2.58f );
	m_pinkPoints.SetZ(pos.z   - 2.58f );

	m_redPoints.Update();
	m_greenPoints.Update();
	m_yellowPoints.Update();
	m_pinkPoints.Update();

	m_red.SetPosition(    b2Vec2(pos.x - 1.2f    , pos.y - 1 ));
	m_green.SetPosition(  b2Vec2(pos.x - 0.4f    , pos.y - 1 ));
	m_yellow.SetPosition( b2Vec2(pos.x + 0.4f    , pos.y - 1 ));
	m_pink.SetPosition(   b2Vec2(pos.x + 1.2f    , pos.y - 1 ));

	m_red.SetZ(pos.z    - 2.6f );
	m_green.SetZ(pos.z  - 2.6f );
	m_yellow.SetZ(pos.z - 2.6f );
	m_pink.SetZ(pos.z   - 2.6f );

	m_red.Update();
	m_green.Update();
	m_yellow.Update();
	m_pink.Update();
}
