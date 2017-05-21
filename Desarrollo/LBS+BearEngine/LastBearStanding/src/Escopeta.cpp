#include "PhysicBody/PBCogibleReleased.h"
#include "PhysicBody/PBCogibleCatched.h"
#include "PhysicBody/PBCap.h"
#include "Particle.h"
#include "Escopeta.h"
#include "World.h"
#include "BearManager.h"
#include "Bala.h"
#include "SDL.h"

Escopeta::Escopeta(Spawner* expo, int modelo,b2Vec2 pos, int id)
:Usable(new PBCogibleCatched, expo,pos,glm::vec3(0.07f,0.02f,0.002f),"BearEngine/res/escopeta.obj","media/Images/escopetatex.png", id){
    usos = 3;
}
Escopeta::~Escopeta(){}
void Escopeta::usar(){
    if(usos){
        if(SDL_GetTicks()-timeCadencia > cadencia ){
            for(int i=0; i<10; i++){
                float desvBala = rand()% 10 - 10;
                float velBala = rand()% 3 + 10;
                m_pWorld->AddBala(new Bala(b2Vec2(m_gameObject.GetPosition().x,-(m_gameObject.GetPosition().y)), 200, velBala, desvBala, dir, 1));
            }
            Particle *cap = m_pWorld->AddParticle(new Particle(new PBCap(),b2Vec2(m_gameObject.GetPosition().x/2.0f,-(m_gameObject.GetPosition().y/2.0f)),glm::vec3(0.013f,.01f,.01f)));
            b2Vec2 capVel;
            capVel.x = (dir*(rand()%16+0.5f)/10.f)+0.5f;
            capVel.y =((rand()%19+0.5f)/10.f)+0.5f;
            cap->SetLinearVelocity(capVel);
            cap->SetAngularVelocity(((rand()%4+0.5f)/10.f)+0.5f);
            timeCadencia = SDL_GetTicks();
            usos--;
        }
    }else{CompruebaVida();}
}
