
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
	device = createDevice( irr::video::EDT_OPENGL, deskres, 32, true, true, true, myEventReceiver );
	driver = device->getVideoDriver();
	device->setWindowCaption(L"Irrlicht/Box2D Sample");
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	smgr->addLightSceneNode(0, irr::core::vector3df(-15,5,-10),irr::video::SColorf(1.0f, 1.0f, 1.0f));
    smgr->setAmbientLight(irr::video::SColor(0,60,60,60));
	//smgr->addLightSceneNode(0, irr::core::vector3df(0,-90,-30) );
	timer = device->getTimer();
}
void IrrManager::Update(){
	smgr->drawAll();
	guienv->drawAll();
	endScene();
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
    return  mesh;
}
irr::io::IXMLReader* IrrManager::createXMLReader(irr::core::stringw file){return device->getFileSystem()->createXMLReader(file);}
float IrrManager::getTime(){return timer->getTime();}
void IrrManager::beginScene(){driver->beginScene(true, true, irr::video::SColor(0,196, 218, 255));}
void IrrManager::endScene(){driver->endScene();}
void IrrManager::drop(){driver->drop();}
irr::scene::ISceneManager* IrrManager::getManager(){return smgr;}
MyEventReceiver* IrrManager::getEventReciever(){return myEventReceiver;}
irr::IrrlichtDevice* IrrManager::getDevice(){return device;}
irr::video::IVideoDriver* IrrManager::getDriver(){return driver;}
irr::gui::IGUIEnvironment* IrrManager::getGUI(){return guienv;}
irr::ITimer* IrrManager::getTimer(){return timer;}
IrrManager::~IrrManager(){}
