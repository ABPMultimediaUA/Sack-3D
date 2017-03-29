
#include "IrrManager.h"
#include "MyEventReceiver.h"
#include "DebugInfo.h"
#include "HUD.h"

IrrMngr* IrrMngr::pinstance = 0;
IrrMngr* IrrMngr::Inst(){
	if(pinstance == 0){
		pinstance = new IrrMngr;
	}
	return pinstance;
}
void IrrMngr::Reset(){
    smgr->clear();
}
void IrrMngr::Close(){device->closeDevice();}
IrrMngr::IrrMngr():m_debugMode(false){
	irr::IrrlichtDevice *nulldevice = irr::createDevice(irr::video::EDT_NULL);
	myEventReceiver = new MyEventReceiver();
	irr::core::dimension2d<irr::u32> deskres = nulldevice->getVideoModeList()->getDesktopResolution();
	device = createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(500*16/9,500), 32, false, true, true, myEventReceiver );
	//device = createDevice( irr::video::EDT_OPENGL, deskres, 32, true, true, true, myEventReceiver );
	driver = device->getVideoDriver();
	device->setWindowCaption(L"Last Bear Standing");
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	smgr->addLightSceneNode(0, irr::core::vector3df(-15,5,-10),irr::video::SColorf(1.0f, 1.0f, 1.0f));
    smgr->setAmbientLight(irr::video::SColor(0,60,60,60));
	timer = device->getTimer();
	//device->setResizable(true);
}
void IrrMngr::InstanciaVariables(int* puntuaciones){
  	debugInfo.Reset(new DebugInfo());
  	hud.Reset(new HUD(puntuaciones,smgr->getVideoDriver()->getScreenSize().Width,smgr->getVideoDriver()->getScreenSize().Height));
}
void IrrMngr::Update(){
	smgr->drawAll();
	hud.Get()->Draw();
	if(m_debugMode)
		debugInfo.Get()->Draw(smgr->getVideoDriver()->getFPS());
	endScene();
}
irr::scene::IMeshSceneNode* IrrMngr::addCubeSceneNode(irr::core::vector3df tam,irr::video::SColor color){
	irr::scene::IMesh* mesh = smgr->getGeometryCreator()->createCubeMesh(tam);
	irr::scene::IMeshSceneNode* node = smgr->addMeshSceneNode(mesh);
    smgr->getMeshManipulator()->setVertexColors(node->getMesh(), color);
	return node;
}
irr::scene::IMesh* IrrMngr::createCubeMesh(irr::core::vector3df pos, irr::core::vector3df tam, irr::video::SColor color){
	irr::scene::IMesh* mesh = smgr->getGeometryCreator()->createCubeMesh(tam);
	smgr->addMeshSceneNode(mesh)->setPosition(pos);
    smgr->getMeshManipulator()->setVertexColors(mesh, color);
    return  mesh;
}

void  IrrMngr::SwitchDebugMode(){
  if(m_debugMode){
    m_debugMode = false;
  }
  else{
    m_debugMode = true;
  }
}
irr::io::IXMLReader* IrrMngr::createXMLReader(irr::core::stringw file){return device->getFileSystem()->createXMLReader(file);}
float IrrMngr::getTime(){return timer->getTime();}
void IrrMngr::beginScene(){driver->beginScene(true, true, irr::video::SColor(0,196, 218, 255));}
void IrrMngr::endScene(){driver->endScene();}
void IrrMngr::drop(){driver->drop();}
irr::scene::ISceneManager* IrrMngr::getManager(){return smgr;}
MyEventReceiver* IrrMngr::getEventReciever(){return myEventReceiver;}
irr::IrrlichtDevice* IrrMngr::getDevice(){return device;}
irr::video::IVideoDriver* IrrMngr::getDriver(){return driver;}
irr::gui::IGUIEnvironment* IrrMngr::getGUI(){return guienv;}
irr::ITimer* IrrMngr::getTimer(){return timer;}
IrrMngr::~IrrMngr(){}
