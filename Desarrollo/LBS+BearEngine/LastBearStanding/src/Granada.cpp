#include "PhysicBody/PBGranadaReleased.h"
#include "PhysicBody/PBCogibleCatched.h"
#include "PhysicBody/PBCotton.h"
#include "BearManager.h"
#include "Metralla.h"
#include "Spawner.h"
#include "Granada.h"
#include "Particle.h"
#include "World.h"
#include "Client.h"
#include "SDL.h"

Granada::Granada(Spawner* expo,int modelo,b2Vec2 pos, int id)
:Usable(new PBCogibleCatched,expo,pos,glm::vec3(.05f,.05f,.05f),"BearEngine/res/granada.obj","media/Images/granadatex.png", id),mecha(3000){
  usos = 1;
  usada = false;
  cogedor=-1;
  timerGranada = SDL_GetTicks();
}
Granada::~Granada(){}
void Granada::actualiza(){
  Cogible::actualiza();
  if(!autoDestruir && SDL_GetTicks() - timerGranada > mecha && usada){
    if(cogido)World::Inst()->getPlayer(cogedor)->Soltar();
    Explosion();
    autoDestruir = true;
  }
}
void Granada::setCogedor(int aux){
    cogedor = aux;
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
    }
    cogido = aux;
}
void Granada::usar(){
  if(!usada){
        //int id = (*Client::Inst()->getIdCliente())-'0';
        World::Inst()->getPlayer(cogedor)->Soltar();
        timerGranada = SDL_GetTicks();
        usada=true;
        usos --;
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
