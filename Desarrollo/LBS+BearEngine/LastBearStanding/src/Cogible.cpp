#include "PhysicBody/PBCogibleReleased.h"
#include "PhysicBody/PBCogibleCatched.h"
#include "BearManager.h"
#include "Cogible.h"
#include "Spawner.h"
#include "World.h"

Cogible::Cogible(PhysicBody* physicBody ,Spawner* expo, b2Vec2 pos, glm::vec3 tam, char *model, char *texture, int idc){
    m_id = m_gameObject.Inicialize(physicBody,pos,tam,model,texture);
    m_pWorld =   World::Inst();
    m_pBearMngr = BearMngr::Inst();
    autoDestruir = false;
    cogido = false;
    teletransportado = false;
    dir = 1;
    expuesto = true;
    if(expo == NULL)expuesto = false;
    expositor = expo;
    id=idc;
}
Cogible::~Cogible(){}
void Cogible::actualiza(){
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
    }
    cogido = aux;
}
void Cogible::teletransportar(){
    teletransportado = false;
    if(dir != 0){
        nextPos.x += (dir*2);
    }
    else{ nextPos.x += 1.5f;}
    b2Vec2 velActual = m_gameObject.GetLinearVelocity();
    m_gameObject.SetPosition(b2Vec2(nextPos.x,nextPos.y));
    m_gameObject.SetRotation(m_gameObject.GetRotation());
    m_gameObject.SetLinearVelocity(velActual);
}
/*if(lastDir ==  0)       m_gameObject.SetXRotation(0);
    else if(lastDir == -1)  m_gameObject.SetXRotation(180);*/
void Cogible::setDireccion(int d){
    if(d != 0){
        dir = d;
        m_gameObject.SetMargin(b2Vec2(0.01f*d,0));
    }
    if(cogido){
         if(d == 1)         m_gameObject.SetXRotation(0);
         else if(d == -1)   m_gameObject.SetXRotation(180);
    }
}
b2Vec2   Cogible::GetPosition(){return m_gameObject.GetPosition();}
int     Cogible::getDireccion(){return dir;}
void     Cogible::setExpositor(Spawner* aux){expositor=aux;}
void     Cogible::setNextPos(b2Vec2 pos){teletransportado=true; nextPos = pos;}
void     Cogible::setExpuesto(bool aux){expuesto = aux;}
Spawner* Cogible::getExpositor(){return expositor;}
bool     Cogible::getCogido(){return cogido;}
bool     Cogible::getAutoDestruir(){return autoDestruir;}
int      Cogible::GetId(){return m_id;}
int      Cogible::GetIdc(){return id;}
bool     Cogible::getExpuesto(){return expuesto;}
b2Vec2   Cogible::GetLinearVelocity(){return m_gameObject.GetLinearVelocity();}
float    Cogible::GetRotation(){return m_gameObject.GetRotation();}
void     Cogible::SetAngularVelocity(float imp){m_gameObject.SetAngularVelocity(imp);}
void     Cogible::SetLinearVelocity(b2Vec2 vel){m_gameObject.SetLinearVelocity(vel);}
