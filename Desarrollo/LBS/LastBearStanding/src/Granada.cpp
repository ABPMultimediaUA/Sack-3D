#include "PhysicBody/PBGranadaReleased.h"
#include "PhysicBody/PBCogibleCatched.h"
#include "PhysicBody/PBCotton.h"
#include "IrrManager.h"
#include "Metralla.h"
#include "Spawner.h"
#include "Granada.h"
#include "Particle.h"
#include "World.h"
#include "Client.h"
#include "Bot.h"

Granada::Granada(Spawner* expo,int modelo,b2Vec2 pos)
:Usable(new PBCogibleCatched,expo,pos,irr::core::vector3df(.05f,.05f,.05f),irr::video::SColor(30, 100, 30, 0)),mecha(3000){
  usada = false;
  cogedor=-1;
  timerIrr = IrrMngr::Inst()->getTimer();
}
Granada::~Granada(){}
void Granada::actualiza(){
  Cogible::actualiza();
  if(!autoDestruir && timerIrr->getTime() - timerGranada > mecha && usada){
    if(cogido)World::Inst()->getPlayer(cogedor)->Soltar();
    Explosion();
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
        m_gameObject.SetMargin(b2Vec2(0.5f*dir,0));
    }
    else{
        m_id = m_gameObject.SetMode(new PBGranadaReleased());
        m_gameObject.SetMargin(b2Vec2(0,0));
    }
    cogido = aux;
}

void Granada::setCogedor(int aux){
    cogedor = aux;
}
void Granada::usar(){
  if(!usada){
        int id = (*Client::Inst()->getIdCliente())-'0';
        if(id == cogedor)World::Inst()->getPlayer(cogedor)->CogerTirar();
        if(dynamic_cast<Bot*>(World::Inst()->getPlayer(cogedor)))World::Inst()->getPlayer(cogedor)->CogerTirar();
        timerGranada = timerIrr->getTime();
        usada=true;
        cogedor = -1;
    }
}
void Granada::Explosion(){
    b2Vec2 pos = m_gameObject.GetPosition();
    pos.y *= -1;
    pos.x=pos.x/2.0f;
    pos.y=pos.y/2.0f;
    for (int i = 0; i < 25; ++i){
        b2Vec2 capVel;
        capVel.x = ((rand()%100-50)/10.f);
        capVel.y = ((rand()%100-50)/10.f);
        m_pWorld->AddMetralla(new Metralla(pos,capVel));
    }
}
