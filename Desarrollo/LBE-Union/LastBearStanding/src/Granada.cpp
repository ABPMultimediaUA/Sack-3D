#include "PhysicBody/PBGranadaReleased.h"
#include "PhysicBody/PBCogibleCatched.h"
#include "IrrManager.h"
#include "Metralla.h"
#include "Spawner.h"
#include "Granada.h"
#include "World.h"
#include "Client.h"

Granada::Granada(Spawner* expo,int modelo,b2Vec2 pos)
:Usable(new PBCogibleCatched,expo,pos,irr::core::vector3df(.01f,.01f,.01f),irr::video::SColor(30, 100, 30, 0)),mecha(3000){
  usada = false;
  timerIrr = IrrMngr::Inst()->getTimer();
}
Granada::~Granada(){}
void Granada::actualiza(){
  if(!autoDestruir)Cogible::actualiza();
  if(timerIrr->getTime() - timerGranada > mecha && usada && !autoDestruir){
    for (int i = 0; i < PARTICULAS; i++) {
      float angle = (i / (float)PARTICULAS) * 360;
      b2Vec2 rayDir( sinf(angle), cosf(angle) );
      m_pWorld->AddMetralla(new Metralla(m_gameObject.GetPosition(),200 * rayDir));
    }
    autoDestruir = true;
  }
}
void Granada::setCogido(bool aux){
    if(aux){
        if(expuesto){
            expositor->soltar();
            expuesto = false;
        }
        m_id = m_gameObject.SetMode(new PBCogibleCatched());
    }
    else{
        m_id = m_gameObject.SetMode(new PBGranadaReleased());
        m_gameObject.SetMargin(b2Vec2(0.5f*dir,0));
    }
    cogido = aux;
}
void Granada::usar(){
  if(!usada){
        int id = (*Client::Inst()->getIdCliente())-'0';
        World::Inst()->getPlayer(id)->CogerTirar();
        timerGranada = timerIrr->getTime();
        usada=true;
    }
}
