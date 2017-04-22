#ifndef IRRMANAGER_H
#define IRRMANAGER_H

#include <irrlicht.h>
#include "GameResource.h"
#include "glm/glm.hpp"

class DebugInfo;
class HUD;
class MyEventReceiver;
class TMotorBear;
class TNodo;
class Shader;


class IrrMngr{
    public:
        static IrrMngr* Inst();
        IrrMngr();
        void Update();
        void InstanciaVariables(int* puntuaciones);
        void Reset();
        void beginScene();
        void endScene();
        void drop();
        float getTime();
        void Close();
        irr::gui::IGUIFont* getFont();
        irr::scene::IMesh* createCubeMesh(irr::core::vector3df pos, irr::core::vector3df tam,  irr::video::SColor color);
        irr::scene::IMeshSceneNode* addCubeSceneNode(int tam , irr::video::SColor color);
        irr::scene::IMeshSceneNode* addCubeSceneNode(irr::core::vector3df tam, irr::video::SColor color);
        irr::io::IXMLReader* createXMLReader(irr::core::stringw file);
        //BearEngine
        TNodo* CreateBearNode(int id,glm::vec3 pos, glm::vec3 tam);
        void SetBearCubePosition(TNodo* nodo,glm::vec3 pos );
        void SetBearCubeRotation(TNodo* nodo, float rot);
        void SetBearCameraPosition(float x, float y, float z);
        void RemoveBearNode(TNodo* nodo);
        void IsBearVisible(TNodo* nodo, bool visible);
        //BearEngine
        irr::scene::ISceneManager* getManager();
        MyEventReceiver* getEventReciever();
        irr::IrrlichtDevice* getDevice();
        irr::video::IVideoDriver* getDriver();
        irr::gui::IGUIEnvironment* getGUI();
        irr::ITimer* getTimer();
        void  SwitchDebugMode();
        void setBackgroundImage(irr::video::ITexture* bimage);
        virtual ~IrrMngr();
    private:
        static IrrMngr* pinstance;
        static const unsigned int m_windowSize;
        irr::scene::ISceneManager* smgr;
        irr::IrrlichtDevice* device;
        irr::video::IVideoDriver* driver;
        irr::ITimer* timer;
        irr::gui::IGUIEnvironment* guienv;
        MyEventReceiver* myEventReceiver;
        GameResource<DebugInfo> debugInfo;
        GameResource<HUD> hud;
        GameResource<TMotorBear> m_gMotorBear;
        GameResource<Shader> m_gShader;
        TMotorBear* m_motorBear;
        TNodo* m_camara;
        Shader* m_shader;
        irr::video::ITexture* m_backgroundImage;
        unsigned int m_windowWidth;
        unsigned int m_windowHeight;
        bool m_debugMode;
};

#endif
