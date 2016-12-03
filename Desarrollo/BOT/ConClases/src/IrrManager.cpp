#include "IrrManager.h"

#define SCREENWIDTH 1366
#define SCREENHEIGHT 720

IrrManager* IrrManager::pinstance = 0;
IrrManager* IrrManager::Instance(){
	if(pinstance == 0){
		pinstance = new IrrManager;
	}
	return pinstance;
}
IrrManager::IrrManager(){
	receiver = new MyEventReceiver();
	device = createDevice( video::EDT_OPENGL, dimension2d<u32>(SCREENWIDTH,SCREENHEIGHT), 32, true, true, true, receiver);
    driver = device->getVideoDriver();
    device->setWindowCaption(L"Irrlicht/Box2D Sample");
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();
    guienv->addStaticText(L"Box2D integrated with Irrlicht", rect<s32>(10,10,130,22), true);
	//smgr->addCameraSceneNode(0, vector3df(0,0,-140), vector3df(0,0,0));
	smgr->addLightSceneNode(0, vector3df(0,100,-100), video::SColorf(1,1,1), 40.f);
    timer = device->getTimer();
}
void IrrManager::drawAll(){
	smgr->drawAll();
	guienv->drawAll();
}
IMeshSceneNode* IrrManager::addCubeSceneNode(int tam,SColor color){
	IMeshSceneNode* node = smgr->addCubeSceneNode(tam);
	smgr->getMeshManipulator()->setVertexColors(node->getMesh(), color);
	return node;
}
IMeshSceneNode* IrrManager::addCubeSceneNode(vector3df tam,SColor color){
	IMesh* mesh = smgr->getGeometryCreator()->createCubeMesh(tam);
	IMeshSceneNode* node = smgr->addMeshSceneNode(mesh);
    smgr->getMeshManipulator()->setVertexColors(node->getMesh(), color);
	return node;
}
IMesh* IrrManager::createCubeMesh(vector3df pos, vector3df tam, SColor color){
	IMesh* mesh = smgr->getGeometryCreator()->createCubeMesh(tam);
	smgr->addMeshSceneNode(mesh)->setPosition(pos);
    smgr->getMeshManipulator()->setVertexColors(mesh, color);
}
IXMLReader* IrrManager::createXMLReader(stringw file){return device->getFileSystem()->createXMLReader(file);}
float IrrManager::getTime(){return timer->getTime();}
void IrrManager::beginScene(){driver->beginScene(true, true, SColor(255,100,101,140));}
void IrrManager::endScene(){driver->endScene();}
void IrrManager::drop(){driver->drop();}
ISceneManager* IrrManager::getManager(){return smgr;}
MyEventReceiver* IrrManager::getEventReciever(){return receiver;}
IrrlichtDevice* IrrManager::getDevice(){return device;}
IVideoDriver* IrrManager::getDriver(){return driver;}
IGUIEnvironment* IrrManager::getGUI(){return guienv;}
ITimer* IrrManager::getTimer(){return timer;}
IrrManager::~IrrManager(){}
