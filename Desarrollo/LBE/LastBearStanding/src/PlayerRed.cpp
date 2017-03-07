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
    m_pBody->SetLinearVelocity(b2Vec2 (moviendo*vel, m_pBody->GetLinearVelocity().y));
    if(cogiendo) objCogido->setDireccion(direccion);
}

void PlayerRed::actualiza(){
    m_pNode->setPosition(irr::core::vector3df(m_pBody->GetPosition().x,m_pBody->GetPosition().y,0));
    m_pNode->setRotation(irr::core::vector3df(0,0,m_pBody->GetAngle()*RADTOGRAD));
    mover(moviendo);
}

void PlayerRed::setPos(){
    m_pBody->SetTransform(b2Vec2(x,y), m_pBody->GetAngle());
}

void PlayerRed::usar(){
    if(cogiendo)if( Usable* usable = dynamic_cast<Usable*>(objCogido)){
        usable->usar();
    }
}

void PlayerRed::saltar(int i){
    if(i==1){
        b2Vec2 velV = m_pBody->GetLinearVelocity();
        velV.y = salto;
        m_pBody->SetLinearVelocity(velV);
    }
    else if(i==2){
        b2Vec2 velV = m_pBody->GetLinearVelocity();
        velV.y = salto*3/4;
        m_pBody->SetLinearVelocity(velV);
    }
}
void PlayerRed::CogerTirar(int idCogible){
    if(idCogible!=-1){
        for (unsigned int i = 0; i <m_pWorld->GetCogibles().size(); ++i){
            if(m_pWorld->GetCogibles().at(i)->getIdCogible()==idCogible){
              objCogido = m_pWorld->GetCogibles().at(i);
            }
        }
        objCogido = objPuedoCoger;
        objCogido->setCogido(true);
        b2RevoluteJointDef jointDef;
        jointDef.bodyA = m_pBody;
        jointDef.bodyB = objPuedoCoger->getBody();
        jointDef.localAnchorA.Set(0,0.3f);
        jointDef.localAnchorB.Set(0,0);
        joint = (b2RevoluteJoint*)m_pWorld->GetWorld()->CreateJoint(&jointDef);
        joint->EnableMotor(true);
        cogiendo = true;
    }else{
        Soltar();
    }
}
void PlayerRed::morirRed(){
    paraMorir = false;
    if(cogiendo) Soltar();
    DestroyFixtures();
    estado = MUERTO_DORMIDO;
    InicializeFixtures(MUERTO_DORMIDO);
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


