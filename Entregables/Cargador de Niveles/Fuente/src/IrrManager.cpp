/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          IrrManager.cpp

Author:        Estudio Rorschach
Created:       11/11/2016 Jorge Puerto
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que controla todo lo relacionado con en mundo tridimensional, la pantalla
temporizadores, entorno, graficos...

ToDo:
Hay mucho que aprender sobre esta gran mierda llamada irrlicht
*******************************************************************************/
#include "IrrManager.h"

#define SCREENWIDTH 1366
#define SCREENHEIGHT 768

/******************************************************************************
                               IrrManager
*******************************************************************************/

//---------------------------------------------------------------------------
/**
   Instancia
*/
IrrManager* IrrManager::pinstance = 0;
IrrManager* IrrManager::Instance(){
	if(pinstance == 0){
		pinstance = new IrrManager;
	}
	return pinstance;
}
//---------------------------------------------------------------------------
/**
   Constructor
*/
IrrManager::IrrManager(){
	receiver = new MyEventReceiver();
	device = createDevice( video::EDT_OPENGL, dimension2d<u32>(SCREENWIDTH,SCREENHEIGHT), 32, true, true, true, receiver);
    driver = device->getVideoDriver();
    device->setWindowCaption(L"Irrlicht/Box2D Sample");
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();
	smgr->addLightSceneNode(0, vector3df(0,100,-100), video::SColorf(1,1,1), 40.f);
    timer = device->getTimer();
}
//---------------------------------------------------------------------------
/**
   Dibuja el mundo
*/
void IrrManager::drawAll(){
	smgr->drawAll();
	guienv->drawAll();
}
//---------------------------------------------------------------------------
/**
   Genera un nodo cubico pasando tamaño y color
*/
IMeshSceneNode* IrrManager::addCubeSceneNode(int tam,SColor color){
	IMeshSceneNode* node = smgr->addCubeSceneNode(tam);
	smgr->getMeshManipulator()->setVertexColors(node->getMesh(), color);
	return node;
}
//---------------------------------------------------------------------------
/**
   Genera un nodo rectangular pasando posicion, tamaño y color
*/
IMeshSceneNode* IrrManager::addCubeSceneNode(vector3df tam,SColor color){
	IMesh* mesh = smgr->getGeometryCreator()->createCubeMesh(tam);
	IMeshSceneNode* node = smgr->addMeshSceneNode(mesh);
    smgr->getMeshManipulator()->setVertexColors(node->getMesh(), color);
	return node;
}
//---------------------------------------------------------------------------
/**
   Genera una malla rectangular pasando posicion, tamaño y color
*/
IMesh* IrrManager::createCubeMesh(vector3df pos, vector3df tam, SColor color){
	IMesh* mesh = smgr->getGeometryCreator()->createCubeMesh(tam);
	smgr->addMeshSceneNode(mesh)->setPosition(pos);
    smgr->getMeshManipulator()->setVertexColors(mesh, color);
}
IXMLReader* IrrManager::createXMLReader(stringw file){return device->getFileSystem()->createXMLReader(file);}
//---------------------------------------------------------------------------
/**
   ????????????????????????????
*/
float IrrManager::getTime(){return timer->getTime();}
//---------------------------------------------------------------------------
/**
   ????????????????????????????
*/
void IrrManager::beginScene(){driver->beginScene(true, true, SColor(255,100,101,140));}
//---------------------------------------------------------------------------
/**
   ????????????????????????????
*/
void IrrManager::endScene(){driver->endScene();}
//---------------------------------------------------------------------------
/**
   ????????????????????????????
*/
void IrrManager::drop(){driver->drop();}
//---------------------------------------------------------------------------
/**
   ????????????????????????????
*/
ISceneManager* IrrManager::getManager(){return smgr;}//---------------------------------------------------------------------------
/**
   Getters y setters
*/
MyEventReceiver* IrrManager::getEventReciever(){return receiver;}
IrrlichtDevice* IrrManager::getDevice(){return device;}
IVideoDriver* IrrManager::getDriver(){return driver;}
IGUIEnvironment* IrrManager::getGUI(){return guienv;}
ITimer* IrrManager::getTimer(){return timer;}
//---------------------------------------------------------------------------
/**
   Destructor
*/
IrrManager::~IrrManager(){}
