#ifndef BEARMANAGER_H
#define BEARMANAGER_H

#include "GameResource.h"
#include "glm/glm.hpp"

class DebugInfo;
class MyEventReceiver;
class TMotorBear;
class TNodo;


class BearMngr{
    public:
        static BearMngr* Inst();
        BearMngr();
        void Update();
        void InstanciaVariables(int* puntuaciones);
        TNodo* CreateBearCube(int id,glm::vec3 pos, glm::vec3 tam,char* texture, bool shader = 1);
        TNodo* CreateBearModel(int id,glm::vec3 pos,char* model,char* texture);
        void   AddModel(TNodo* nodo, char* model);
        void NextFrame(TNodo* nodo);
        void ResetAnimacion(TNodo* nodo);
        void SetBearCubePosition(TNodo* nodo,glm::vec3 pos );
        void SetBearCubeRotation(TNodo* nodo, float rot);
        void SetXRotation(TNodo* nodo,float);
        void SetBearCameraPosition(float x, float y, float z);
        void RemoveBearNode(TNodo* nodo);
        void IsBearVisible(TNodo* nodo, bool visible);
        bool IsClosed();
        void  SwitchDebugMode();
        TMotorBear* getMotorBear(){return m_motorBear;}
        //void setBackgroundImage(irr::video::ITexture* bimage);
        unsigned int getWidth(){return m_windowWidth;}
        unsigned int getHeight(){return m_windowHeight;}
        virtual ~BearMngr();
    private:
        static BearMngr* pinstance;
        static const unsigned int m_windowSize;
        MyEventReceiver* myEventReceiver;
        GameResource<DebugInfo> debugInfo;
        GameResource<TMotorBear> m_gMotorBear;
        TMotorBear* m_motorBear;
        TNodo* m_camara;
        //irr::video::ITexture* m_backgroundImage;
        unsigned int m_windowWidth;
        unsigned int m_windowHeight;
        bool m_debugMode;
};

#endif
