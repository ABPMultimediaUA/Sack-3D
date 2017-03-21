#include "PhysicBody/PBDeadPlayer.h"
#include "PhysicBody/PBAlivePlayer.h"
#include "PlayerRed.h"
#include "World.h"
#include "Usable.h"

PlayerRed::PlayerRed(b2Vec2 pos, int mando, irr::video::SColor color, char idr[])
:Player(pos,mando,color){
    primera = true;
    strncpy(id, idr, sizeof(id));
    estadoAntiguo=LEVANTADO;
}
PlayerRed::~PlayerRed(){}
void PlayerRed::mover(int mov){
    if(primera){
        primera=false;
    }
    if(moviendo == 1){direccion = moviendo = mov;}
    else if(moviendo == -1){direccion = moviendo = mov;}
    else{moviendo = mov;}
    m_gameObject.SetLinearVelocity(b2Vec2 (moviendo*vel, m_gameObject.GetLinearVelocity().y));
    if(cogiendo) objCogido->setDireccion(direccion);
}

void PlayerRed::actualiza(){
    m_gameObject.Update();
    mover(moviendo);
}

void PlayerRed::setPos(){
    m_gameObject.SetPosition(b2Vec2(x,y));
    m_gameObject.SetRotation(m_gameObject.GetRotation());
}

void PlayerRed::usar(){
    if(cogiendo)if( Usable* usable = dynamic_cast<Usable*>(objCogido)){
        usable->usar();
    }
}

void PlayerRed::saltar(int i){
    b2Vec2 velV;
    if(i==0){
        velV.x = 0;
        velV.y = 2;
        m_gameObject.SetLinearVelocity(velV);
        m_gameObject.SetAngularVelocity(rand()%4 - 2);
    }
    if(i==1){
        velV = m_gameObject.GetLinearVelocity();
        velV.y = salto;
        m_gameObject.SetLinearVelocity(velV);
    }
    else if(i==2){
        velV = m_gameObject.GetLinearVelocity();
        velV.y = salto*3/4;
        m_gameObject.SetLinearVelocity(velV);
    }
}
void PlayerRed::CogerTirar(int idCogible){
    //if(idCogible!=-1){
    //    for (unsigned int i = 0; i <m_pWorld->GetCogibles().size(); ++i){
    //        if(m_pWorld->GetCogibles().at(i)->GetId()==idCogible){
    //          objCogido = m_pWorld->GetCogibles().at(i);
    //        }
    //    }
    //    objCogido = objPuedoCoger;
    //    objCogido->setCogido(true);
    //    b2RevoluteJointDef jointDef;
    //    jointDef.bodyA = m_gameObject;
    //    jointDef.bodyB = objPuedoCoger->getBody();
    //    jointDef.localAnchorA.Set(0,0.3f);
    //    jointDef.localAnchorB.Set(0,0);
    //    joint = (b2RevoluteJoint*)m_pWorld->GetWorld()->CreateJoint(&jointDef);
    //    joint->EnableMotor(true);
    //    cogiendo = true;
    //}else{
    //    Soltar();
    //}
}
void PlayerRed::morirRed(){
    paraMorir = false;
    if(cogiendo) Soltar();
    estado = MUERTO_DORMIDO;
    m_id = m_gameObject.SetMode(new PBDeadPlayer);
    muerto = true;
}
void PlayerRed::setx(long int aux){x = aux/1000000.f;}
void PlayerRed::sety(long int aux){y = aux/1000000.f;}
void PlayerRed::setEstado(int aux){estado = aux;}
void PlayerRed::setDireccion(int aux){
    direccion = aux;
    if(cogiendo) objCogido->setDireccion(direccion);
}
void PlayerRed::setMoviendo(int aux){moviendo = aux;}
void PlayerRed::setId(char aux[]){strncpy(id, aux, sizeof(id));}
void PlayerRed::setMuerto(bool aux){muerto = aux;}
void PlayerRed::morir(){}


