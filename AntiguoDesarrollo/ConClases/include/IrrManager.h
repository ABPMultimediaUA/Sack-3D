#ifndef IRRMANAGER_H
#define IRRMANAGER_H

#include <irrlicht.h>
#include "MyEventReceiver.h"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class IrrManager
{
    public:
    	static IrrManager* Instance();
        IrrManager();
        void drawAll();
        void beginScene();
        void endScene();
        void drop();
        float getTime();
        IMesh* createCubeMesh(vector3df pos, vector3df tam,  SColor color);
        IMeshSceneNode* addCubeSceneNode(int tam , SColor color);
        ISceneManager* getManager();
        MyEventReceiver* getEventReciever();
        IrrlichtDevice* getDevice();
        IVideoDriver* getDriver();
        IGUIEnvironment* getGUI();
        ITimer* getTimer();
        virtual ~IrrManager();

    private:
    static IrrManager* pinstance;
    ISceneManager* smgr;
    IrrlichtDevice* device;
    MyEventReceiver* receiver;
    IVideoDriver* driver;
    IGUIEnvironment* guienv;
    ITimer* timer;
};

#endif // IRRMANAGER_H
