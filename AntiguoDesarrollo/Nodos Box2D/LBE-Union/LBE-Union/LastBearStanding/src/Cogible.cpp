#include "PhysicBody/PBCogibleReleased.h"
#include "PhysicBody/PBCogibleCatched.h"
#include "IrrManager.h"
#include "Cogible.h"
#include "Spawner.h"
#include "World.h"

Cogible::Cogible(PhysicBody* physicBody ,Spawner* expo, b2Vec2 pos, irr::core::vector3df tam, irr::video::SColor color){
    m_pos = pos;
    m_id = m_gameObject.Inicialize(physicBody,pos,tam,color);
    m_pWorld =   World::Inst();
    m_pIrrMngr = IrrMngr::Inst();
    autoDestruir = false;
    cogido = false;
    teletransportado = false;
    dir = 1;
    expuesto = true;
    if(expo == NULL)expuesto = false;
    expositor = expo;
}
Cogible::~Cogible(){}
void Cogible::actualiza(){
   m_pos = m_gameObject.GetPosition();
   m_gameObject.Update();
}
void Cogible::setCogido(bool aux){
    if(aux){
        if(expuesto){
            expositor->soltar();
            expuesto = false;
        }
        m_id = m_gameObject.SetMode(new PBCogibleCatched());
    }
    else{
        m_id = m_gameObject.SetMode(new PBCogibleReleased());
        m_gameObject.SetMargin(b2Vec2(0.5f*dir,0));
    }
    cogido = aux;
}
void Cogible::teletransportar(){
    teletransportado = false;
    if(dir != 0) nextPos.x += (dir*2);
    else nextPos.x += 1.5f;
    b2Vec2 velActual = m_gameObject.GetLinearVelocity();
    m_gameObject.SetPosition(b2Vec2(nextPos.x,nextPos.y));
    m_gameObject.SetRotation(m_gameObject.GetRotation());
    m_gameObject.SetLinearVelocity(velActual);
}
void     Cogible::setDireccion(int d){
    if(d != 0){
        dir = d;
        m_gameObject.SetMargin(b2Vec2(0.5f*d,0));
    }
}
int     Cogible::getDireccion(){return dir;}
void     Cogible::setExpositor(Spawner* aux){expositor=aux;}
void     Cogible::setNextPos(b2Vec2 pos){teletransportado=true; nextPos = pos;}
void     Cogible::setExpuesto(bool aux){expuesto = aux;}
Spawner* Cogible::getExpositor(){return expositor;}
bool     Cogible::getCogido(){return cogido;}
bool     Cogible::getAutoDestruir(){return autoDestruir;}
int      Cogible::GetId(){return m_id;}
bool     Cogible::getExpuesto(){return expuesto;}
b2Vec2   Cogible::GetLinearVelocity(){return m_gameObject.GetLinearVelocity();}
float    Cogible::GetRotation(){return m_gameObject.GetRotation();}
void     Cogible::SetAngularVelocity(float imp){m_gameObject.SetAngularVelocity(imp);}
void     Cogible::SetLinearVelocity(b2Vec2 vel){m_gameObject.SetLinearVelocity(vel);}
