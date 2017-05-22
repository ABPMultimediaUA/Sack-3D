
#include "BearManager.h"
#include "MyEventReceiver.h"
#include "DebugInfo.h"
#include "HUD.h"
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
	myEventReceiver = new MyEventReceiver();
	m_windowWidth = m_windowSize*16/9;
	m_windowHeight = m_windowSize;
	m_gMotorBear.Reset(new TMotorBear(m_windowWidth,m_windowHeight,"Last Bear Standing"));
    m_motorBear = m_gMotorBear.Get();
    m_camara = m_motorBear->crearObjetoCamaraCompleto(m_motorBear->getRaiz(),"Camara",glm::vec3(0,0,0), 70.0f, 16.f/9.f, 0.01f,1000.0f);
    m_motorBear->activarCamara(m_camara);
}

void BearMngr::InstanciaVariables(int* puntuaciones){
  	//debugInfo.Reset(new DebugInfo());
}
void BearMngr::Update(){
    m_motorBear->Clear(0.5f,0.5f,0.5f,1.0f);
	//if(m_debugMode)
	//	debugInfo.Get()->Draw(smgr->getVideoDriver()->getFPS());
	m_motorBear->draw();
	m_motorBear->UpdateDisplay();
}
//BearEngine
TNodo* BearMngr::CreateBearCube(int id, glm::vec3 pos,glm::vec3 tam, char* texture, bool shader){
    std::ostringstream strm;
    strm << id;

    float   width = tam.x,
            height = tam.y;

    TNodo* nodo = m_motorBear->crearObjetoMallaCompleto(m_motorBear->getRaiz(), "BearEngine/res/cubo.obj",(char*)strm.str().c_str(),shader);
	 if(texture)
        m_motorBear->asignarTextura(nodo,texture);
	 m_motorBear->TrasladarObjeto(nodo,pos);
	 m_motorBear->EscalarObjeto(nodo,tam);
    return nodo;
}
void BearMngr::AddModel(TNodo* nodo, char* model){
    m_motorBear->AsignarMallaANodo(nodo,model);
}
void BearMngr::NextFrame(TNodo* nodo){
    m_motorBear->animarMalla(nodo);
}
void BearMngr::ResetAnimacion(TNodo* nodo){
    m_motorBear->resetAnimacion(nodo);
}

//BearEngine
TNodo* BearMngr::CreateBearModel(int id, glm::vec3 pos,char* model,char* texture){
    std::ostringstream strm;
    strm << id;
	TNodo* nodo = m_motorBear->crearObjetoMallaCompleto(m_motorBear->getRaiz(), model,(char*)strm.str().c_str(),2);
	if(texture)
        m_motorBear->asignarTextura(nodo,texture);
	m_motorBear->TrasladarObjeto(nodo,pos);
    return nodo;
}
void BearMngr::SetBearCubePosition(TNodo* nodo,glm::vec3 pos ){
	m_motorBear->TrasladarObjeto(nodo,pos);
}
void BearMngr::SetBearCubeRotation(TNodo* nodo,float rot ){
    m_motorBear->RotarObjeto(nodo,glm::vec3(0,0,rot));
}
void BearMngr::SetXRotation(TNodo* nodo,float rotation){
    m_motorBear->reiniciarRotacion(nodo);
    m_motorBear->RotarObjeto(nodo,glm::vec3(0,rotation,0));
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
BearMngr::~BearMngr(){}
