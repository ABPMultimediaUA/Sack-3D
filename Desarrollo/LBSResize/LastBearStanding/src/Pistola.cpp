#include "PhysicBody/PBCogibleReleased.h"
#include "PhysicBody/PBCogibleCatched.h"
#include "PhysicBody/PBCap.h"
#include "IrrManager.h"
#include "Particle.h"
#include "Pistola.h"
#include "World.h"
#include "Bala.h"

Pistola::Pistola(Spawner* expo, int modelo,b2Vec2 pos)
:Usable(new PBCogibleCatched(),expo,pos,irr::core::vector3df(0.04f,.02f,.02f),irr::video::SColor(255, 255, 0, 255)){
	usos = 10;
	cadencia = 100;
}
Pistola::~Pistola(){}
void Pistola::usar(){
    if(usos){
        if(m_pIrrMngr->getTime()-timeCadencia > cadencia ){
            float desvBala = /*rand()% 3 - 3*/0;
	    	m_pWorld->AddBala(new Bala(b2Vec2(m_gameObject.GetPosition().x,-(m_gameObject.GetPosition().y)), 300, 10, desvBala, dir,1));
            Particle *cap = m_pWorld->AddParticle(new Particle(new PBCap(),b2Vec2(m_gameObject.GetPosition().x/2.0f,-(m_gameObject.GetPosition().y/2.0f)),irr::core::vector3df(0.006f,.006f,1), irr::video::SColor(255,229, 229, 59)));
	    	b2Vec2 capVel;
	    	capVel.x = (dir*(rand()%6)/10.f)+0.5f;
	    	capVel.y =((rand()%9)/10.f)+0.5f;
	    	cap->SetLinearVelocity(capVel);
	    	cap->SetAngularVelocity(((rand()%4)/10.f)+0.5f);
	    	usos--;
            timeCadencia = timerCadencia->getTime();
	    }
    }
}
