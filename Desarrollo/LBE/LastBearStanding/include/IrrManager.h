
#ifndef IRRMANAGER_H
#define IRRMANAGER_H
#include "MyEventReceiver.h"

class IrrMngr{
    public:
        static IrrMngr* Inst();
        IrrMngr();
        void Update();
        void Reset();
        void beginScene();
        void endScene();
        void drop();
        float getTime();
        void Close();
        irr::scene::IMesh* createCubeMesh(irr::core::vector3df pos, irr::core::vector3df tam,  irr::video::SColor color);
        irr::scene::IMeshSceneNode* addCubeSceneNode(int tam , irr::video::SColor color);
        irr::scene::IMeshSceneNode* addCubeSceneNode(irr::core::vector3df tam, irr::video::SColor color);
        irr::io::IXMLReader* createXMLReader(irr::core::stringw file);
        irr::scene::ISceneManager* getManager();
        MyEventReceiver* getEventReciever();
        irr::IrrlichtDevice* getDevice();
        irr::video::IVideoDriver* getDriver();
        irr::gui::IGUIEnvironment* getGUI();
        irr::ITimer* getTimer();
        virtual ~IrrMngr();
    private:
        static IrrMngr* pinstance;
        irr::scene::ISceneManager* smgr;
        irr::IrrlichtDevice* device;
        irr::video::IVideoDriver* driver;
        irr::ITimer* timer;
        irr::gui::IGUIEnvironment* guienv;
        MyEventReceiver* myEventReceiver;
};

#endif
