#include "PhysicBody/PBDeadPlayer.h"
#include "PhysicBody/PBAlivePlayer.h"
#include "PhysicBody/PBCotton.h"
#include "PlayerRed.h"
#include "Particle.h"
#include "World.h"
#include "Usable.h"
#include "Granada.h"

PlayerRed::PlayerRed(b2Vec2 pos, int mando,char *texture,  char idr[], int ve, int sal)
:Player(pos,texture,mando){
    primera = true;
    strncpy(id, idr, sizeof(id));
    estadoAntiguo=LEVANTADO;
    if(ve!=0){
        vel = ve;
        salto = sal;
    }
    else{
        vel=3.0f;
        salto = 7.0f;
    }
}
PlayerRed::~PlayerRed(){}
void PlayerRed::mover(int mov){
    if(!muerto && !fingiendoMuerte){

        if(primera) primera=false;

        if(moviendo == 1){
            direccion = moviendo = mov;
            //std::cout<<"DIRECCION 1111"<<std::endl;
            }
        else if(moviendo == -1){
            direccion = moviendo = mov;
            //std::cout<<"DIRECCION -1-1-1-1"<<std::endl;
            }
        else{
            moviendo = mov;
            //std::cout<<"DIRECCION 000000"<<std::endl;
            }

        if(mov ==  1)        m_gameObject.SetXRotation(0);
        else if(mov == -1)   m_gameObject.SetXRotation(180);

        m_gameObject.SetLinearVelocity(b2Vec2 (moviendo*vel, m_gameObject.GetLinearVelocity().y));

        if(cogiendo) objCogido->SetLinearVelocity(m_gameObject.GetLinearVelocity());
        if(cogiendo) objCogido->setDireccion(mov);
    }
}

void PlayerRed::actualiza(MyEventReceiver *events){
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
    if(idCogible!=-1){
        //std::cout<<"SOY "<<mando<<"y cojo id "<<idCogible<<std::endl;
        for (unsigned int i = 0; i <m_pWorld->GetCogibles().size(); ++i){
                //std::cout<<m_pWorld->GetCogibles().at(i)->GetIdc()<<std::endl;
            if(m_pWorld->GetCogibles().at(i)->GetIdc()==idCogible){
              objCogido = m_pWorld->GetCogibles().at(i);
              //std::cout<<"ENTRO"<<std::endl;
            }
        }
        //objCogido = objPuedoCoger;
        objCogido->setCogido(true);
        objCogido->setDireccion(1);
        m_gameObject.Catch(objCogido->GetId());
/*
        if(dynamic_cast<Granada*>(objCogido)){
            dynamic_cast<Granada*>(objCogido)->setCogedor(mando);
            std::cout<<"SOY "<<mando<<std::endl;
        }*/

        Granada* gr = dynamic_cast<Granada*>(objCogido);
         if(gr!=NULL){
            gr->setCogedor(mando);
        }

        cogiendo = true;;
    }else{
        Soltar();
    }
}
void PlayerRed::morirRed(){
        b2Vec2 pos = m_gameObject.GetPosition();
        pos.y *= -1;
        pos.x=pos.x/2.0f;
        pos.y=pos.y/2.0f;
        BloodExplosion();
        paraMorir = false;
        if(cogiendo) Soltar();
        estado = MUERTO_DORMIDO;
        m_id = m_gameObject.SetMode(new PBDeadPlayer);
        if(direccion > 0 )
            m_gameObject.SetAngularVelocity(-0.02f);
        else
            m_gameObject.SetAngularVelocity(0.02f);
        muerto = true;
}
void PlayerRed::fingirMuerte(){
    if(cogiendo) Soltar();
    if(muerto)
        return;
    if(!fingiendoMuerte){
        fingiendoMuerte = true;
        m_id = m_gameObject.SetMode(new PBDeadPlayer);
        if(direccion > 0 )
            m_gameObject.SetAngularVelocity(-0.02f);
        else
            m_gameObject.SetAngularVelocity(0.02f);
    }
    else{
        fingiendoMuerte = false;
        m_id = m_gameObject.SetMode(new PBAlivePlayer);
    }
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


