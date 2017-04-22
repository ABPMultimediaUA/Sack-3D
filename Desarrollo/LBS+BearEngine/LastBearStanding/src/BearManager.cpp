
#include "BearManager.h"
#include "MyEventReceiver.h"
#include "DebugInfo.h"
#include "HUD.h"
#include "../BearEngine/include/shader.h"
#include "../BearEngine/include/tmotorbear.h"
#include <sstream>
BearMngr* BearMngr::pinstance = 0;
BearMngr* BearMngr::Inst(){
	if(pinstance == 0){
		pinstance = new BearMngr;
	}
	return pinstance;
}
const unsigned int BearMngr::m_windowSize = 600;

BearMngr::BearMngr():m_debugMode(false){
	irr::IrrlichtDevice *nulldevice = irr::createDevice(irr::video::EDT_NULL);
	myEventReceiver = new MyEventReceiver();
	m_windowWidth = m_windowSize*16/9;
	m_windowHeight = m_windowSize;
	irr::core::dimension2d<irr::u32> deskres = nulldevice->getVideoModeList()->getDesktopResolution();
	//device = createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(m_windowWidth,m_windowSize), 32, false, true, true, myEventReceiver );
	device = createDevice( irr::video::EDT_OPENGL, deskres, 32, true, true, true, myEventReceiver );
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	timer = device->getTimer();
	m_gMotorBear.Reset(new TMotorBear(1080,720,"Last Bear Standing"));
    m_gShader.Reset(new Shader("BearEngine/res/basicShaderLuz"));
    m_motorBear = m_gMotorBear.Get();
    m_shader = m_gShader.Get();
    m_camara = m_motorBear->crearObjetoCamaraCompleto(m_motorBear->getRaiz(),"Camara",glm::vec3(0,0,0), 70.0f, (float)1080/(float)720, 0.01f,1000.0f);
    m_motorBear->activarCamara(m_camara);
    m_motorBear->TrasladarObjeto(m_camara,glm::vec3(10,-10,10));
}
void BearMngr::setBackgroundImage(irr::video::ITexture* bimage){
  	m_backgroundImage = bimage;
}

void BearMngr::InstanciaVariables(int* puntuaciones){
  	debugInfo.Reset(new DebugInfo());
  	hud.Reset(new HUD(puntuaciones,smgr->getVideoDriver()->getScreenSize().Width,smgr->getVideoDriver()->getScreenSize().Height));
}
void BearMngr::Update(){
    m_motorBear->Clear(0.0f,1.15f,0.3f,1.0f);
	m_shader->Bind();
	//hud.Get()->Draw();
	//if(m_debugMode)
	//	debugInfo.Get()->Draw(smgr->getVideoDriver()->getFPS());
	m_motorBear->draw(m_shader);
	m_motorBear->UpdateDisplay();
}
//BearEngine
TNodo* BearMngr::CreateBearNode(int id, glm::vec3 pos,glm::vec3 tam){
    std::ostringstream strm;
    strm << id;
	TNodo* nodo = m_motorBear->crearObjetoMallaCompleto(m_motorBear->getRaiz(), "BearEngine/res/cubo.obj",(char*)strm.str().c_str());
	m_motorBear->TrasladarObjeto(nodo,pos);
	m_motorBear->EscalarObjeto(nodo,tam);
    return nodo;
}
void BearMngr::SetBearCubePosition(TNodo* nodo,glm::vec3 pos ){
	m_motorBear->TrasladarObjeto(nodo,pos);
}
void BearMngr::SetBearCubeRotation(TNodo* nodo,float rot ){
	m_motorBear->RotarObjeto(nodo,glm::vec3(0,0,rot));
}
void BearMngr::SetBearCameraPosition(float x, float y, float z){
    m_motorBear->TrasladarObjeto(m_camara,glm::vec3(x,y,z));
}
void BearMngr::RemoveBearNode(TNodo* nodo){
    m_motorBear->borrarObjeto(nodo);
}
void BearMngr::IsBearVisible(TNodo* nodo, bool visible){
    if(visible)
        m_motorBear->hacerVisibleObjeto(nodo);
    else
        m_motorBear->hacerInvisibleObjeto(nodo);

}
bool BearMngr::IsClosed(){
	return m_motorBear->IsClosed();
}
//BearEngine

void  BearMngr::SwitchDebugMode(){
  if(m_debugMode){
    m_debugMode = false;
  }
  else{
    m_debugMode = true;
  }
}
irr::io::IXMLReader* BearMngr::createXMLReader(irr::core::stringw file){return device->getFileSystem()->createXMLReader(file);}
float BearMngr::getTime(){return timer->getTime();}
irr::scene::ISceneManager* BearMngr::getManager(){return smgr;}
MyEventReceiver* BearMngr::getEventReciever(){return myEventReceiver;}
irr::IrrlichtDevice* BearMngr::getDevice(){return device;}
irr::video::IVideoDriver* BearMngr::getDriver(){return driver;}
irr::gui::IGUIEnvironment* BearMngr::getGUI(){return guienv;}
irr::ITimer* BearMngr::getTimer(){return timer;}
BearMngr::~BearMngr(){}
