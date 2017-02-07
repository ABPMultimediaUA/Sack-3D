
#include "IrrManager.h"
#include "MyEventReceiver.h"

IrrManager* IrrManager::pinstance = 0;
IrrManager* IrrManager::Instance(){
	if(pinstance == 0){
		pinstance = new IrrManager;
	}
	return pinstance;
}
void IrrManager::Close(){device->closeDevice();}
IrrManager::IrrManager(){
  irr::IrrlichtDevice *nulldevice = irr::createDevice(irr::video::EDT_NULL);
  myEventReceiver = new MyEventReceiver();
  irr::core::dimension2d<irr::u32> deskres = nulldevice->getVideoModeList()->getDesktopResolution();
  device = createDevice( irr::video::EDT_OPENGL, deskres, 32, false, true, true, myEventReceiver );
  driver = device->getVideoDriver();
  device->setWindowCaption(L"Irrlicht/Box2D Sample");
  smgr = device->getSceneManager();
  guienv = device->getGUIEnvironment();
  smgr->addLightSceneNode(0, irr::core::vector3df(0,100,-100), irr::video::SColorf(1,1,1), 40.f);
  timer = device->getTimer();
}
void IrrManager::Update(){
	smgr->drawAll();
	guienv->drawAll();
  endScene();
}
irr::scene::IMeshSceneNode* IrrManager::addCubeSceneNode(int tam,irr::video::SColor color){
	irr::scene::IMeshSceneNode* node = smgr->addCubeSceneNode(tam);
	smgr->getMeshManipulator()->setVertexColors(node->getMesh(), color);
	return node;
}
irr::scene::IMeshSceneNode* IrrManager::addCubeSceneNode(irr::core::vector3df tam,irr::video::SColor color){
	irr::scene::IMesh* mesh = smgr->getGeometryCreator()->createCubeMesh(tam);
	irr::scene::IMeshSceneNode* node = smgr->addMeshSceneNode(mesh);
    smgr->getMeshManipulator()->setVertexColors(node->getMesh(), color);
	return node;
}
irr::scene::IMesh* IrrManager::createCubeMesh(irr::core::vector3df pos, irr::core::vector3df tam, irr::video::SColor color){
	irr::scene::IMesh* mesh = smgr->getGeometryCreator()->createCubeMesh(tam);
	smgr->addMeshSceneNode(mesh)->setPosition(pos);
    smgr->getMeshManipulator()->setVertexColors(mesh, color);
}
irr::io::IXMLReader* IrrManager::createXMLReader(irr::core::stringw file){return device->getFileSystem()->createXMLReader(file);}
float IrrManager::getTime(){return timer->getTime();}
void IrrManager::beginScene(){driver->beginScene(true, true, irr::video::SColor(255,100,101,140));}
void IrrManager::endScene(){driver->endScene();}
void IrrManager::drop(){driver->drop();}
irr::scene::ISceneManager* IrrManager::getManager(){return smgr;}
MyEventReceiver* IrrManager::getEventReciever(){return myEventReceiver;}
irr::IrrlichtDevice* IrrManager::getDevice(){return device;}
irr::video::IVideoDriver* IrrManager::getDriver(){return driver;}
irr::gui::IGUIEnvironment* IrrManager::getGUI(){return guienv;}
irr::ITimer* IrrManager::getTimer(){return timer;}
IrrManager::~IrrManager(){}
