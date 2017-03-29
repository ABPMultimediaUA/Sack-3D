#include "PhysicBody/PBDeadPlayer.h"
#include "PhysicBody/PBAlivePlayer.h"
#include "PhysicBody/PBCotton.h"
#include "MyEventReceiver.h"
#include "Particle.h"
#include "Player.h"
#include "Usable.h"
#include "Server/Client.h"
#include "World.h"

Player::Player(b2Vec2 pos, int numMando, irr::video::SColor color)
:Cogible(new PBAlivePlayer,NULL,pos,irr::core::vector3df(.7f, 1.5f,.7f),color),mando(numMando){
    m_pClient = Client::Inst();
    vel = 7;
    moviendoA = 0;
    moviendo = 0;
    salto = 15.0f;
    cogiendo = false;
    puedoCoger = false;
    dobleSaltando = false;
    fingiendoMuerte = false;
    saltando = false;
    paraMorir = false;
    muerto = false;
    teletransportado = false;
    estado = LEVANTADO;
    direccion = 0;
    expuesto = false;
    strncpy(id, m_pClient->getIdCliente(), sizeof(id));
    eventReceiver = IrrMngr::Inst()->getEventReciever();
}
 Player::~Player(){
}
void Player::actualiza(){
    if(teletransportado)teletransportar();
    if(!muerto && paraMorir)morir();
    m_gameObject.Update();
    mover();
}
void Player::mover(){
    if(muerto || fingiendoMuerte)
        return;
    dir = 0;
    int id2 = (*m_pClient->getIdCliente())-'0';
    if(mando == id2){
        if(eventReceiver->IsKeyDown(irr::KEY_KEY_A)){
            moviendo = direccion = dir = -1;
        }
        else if(eventReceiver->IsKeyDown(irr::KEY_KEY_D)){
            moviendo = direccion = dir = 1;
        }
        else{
                moviendo = 0;
        }
    }
    if(moviendo != moviendoA){
        m_pClient->enviarMoviendo(moviendo);
        moviendoA = moviendo;
    }
    m_gameObject.SetLinearVelocity(b2Vec2 (moviendo*vel, m_gameObject.GetLinearVelocity().y));
    if(cogiendo) objCogido->setDireccion(moviendo);
}
void Player::saltar(){
    if(muerto)
        return;
    if(fingiendoMuerte){
        b2Vec2 velV;
        velV.x = 0;
        velV.y = 2;
        m_gameObject.SetLinearVelocity(velV);
        m_gameObject.SetAngularVelocity(rand()%4 - 2);
        m_pClient->enviarSalto(0);
        return;
    }
    if(!saltando){
        b2Vec2 velV = m_gameObject.GetLinearVelocity();
        velV.y = salto;
        m_gameObject.SetLinearVelocity(velV);
        m_pClient->enviarSalto(1);
    }
    else if(!dobleSaltando){
        b2Vec2 velV = m_gameObject.GetLinearVelocity();
        velV.y = salto*3/4;
        m_gameObject.SetLinearVelocity(velV);
        dobleSaltando = true;
        m_pClient->enviarSalto(2);
    }
}
void Player::fingirMuerte(){
    m_pClient->enviarHacerseMuerto();
    if(cogiendo) Soltar();
    if(muerto)
        return;
    if(!fingiendoMuerte){
        fingiendoMuerte = true;
        m_id = m_gameObject.SetMode(new PBDeadPlayer);
        if(direccion > 0 )
            m_gameObject.SetAngularVelocity(-0.5f);
        else
            m_gameObject.SetAngularVelocity(0.5f);
    }
    else{
        fingiendoMuerte = false;
        m_id = m_gameObject.SetMode(new PBAlivePlayer);
    }
}
void Player::morir(){
    if(!muerto){
        b2Vec2 pos = m_gameObject.GetPosition();
        pos.y *= -1;
        for (int i = 0; i < 25; ++i){
            irr::core::vector3df tam;
            tam.X = ((float)(rand()%10)/50.f)+0.01f;
            tam.Y = tam.X;
            tam.Z = 1;
            m_pWorld->AddParticle(new Particle(new PBCotton(),pos,tam, irr::video::SColor(255,100,0,0)));
        }
        paraMorir = false;
        if(cogiendo) Soltar();
        estado = MUERTO_DORMIDO;
        m_id = m_gameObject.SetMode(new PBDeadPlayer);
        if(direccion > 0 )
            m_gameObject.SetAngularVelocity(-0.5f);
        else
            m_gameObject.SetAngularVelocity(0.5f);
        muerto = true;
        m_pClient->enviarMuerto();
    }
}
void Player::CogerTirar(){
    if(!muerto && !fingiendoMuerte){
        if(puedoCoger && !cogiendo){
            Usable* usable = dynamic_cast<Usable*>(objPuedoCoger);
            if(usable && usable->getUsos()){
                objCogido = objPuedoCoger;
                objCogido->setCogido(true);
                objCogido->setDireccion(1);
                m_gameObject.Catch(objCogido->GetId());
                cogiendo = true;
                m_pClient->enviarCogido(objCogido->GetId());
            }
        }
        else if(cogiendo){
            Soltar();
            m_pClient->enviarCogido(-1);
        }
    }
}
void Player::recibeImpulso(float fuerza){
    saltando = true;
    b2Vec2 velV = m_gameObject.GetLinearVelocity();
    velV.y = fuerza;
    m_gameObject.SetLinearVelocity(velV);
}
void Player::Soltar(){
    m_gameObject.Release();
    objCogido->setCogido(false);
    cogiendo = false;
    puedoCoger = false;
    if(m_gameObject.GetLinearVelocity().x > 0 )objCogido->SetAngularVelocity(-2);
    else objCogido->SetAngularVelocity(2);
    b2Vec2 velP = m_gameObject.GetLinearVelocity();
    velP.x*=2;
    velP.y = velP.y*2;
    objCogido->SetLinearVelocity(velP);
    cogiendo =false;
}


void Player::teletransportar(){
    teletransportado = false;
    if(dir != 0) nextPos.x += (dir*2);
    else nextPos.x += 1.5f;
    velActual = m_gameObject.GetLinearVelocity();
    m_gameObject.SetPosition(b2Vec2(nextPos.x,nextPos.y));
    m_gameObject.SetRotation(m_gameObject.GetRotation());
    m_gameObject.SetLinearVelocity(velActual);
}
void Player::usar(){
    if(cogiendo)if( Usable* usable = dynamic_cast<Usable*>(objCogido)){
        m_pClient->enviarUsar();
        usable->usar();
    }
}
b2Vec2 Player::getPosition(){return m_gameObject.GetPosition();}
int Player::getMando(){return mando;}
bool Player::getSaltando(){return saltando;}
bool Player::getDobleSaltando(){return dobleSaltando;}
bool Player::getCogiendo(){return cogiendo;}
bool Player::getPuedoCoger(){return puedoCoger;}
bool Player::getMuerto(){return muerto;}
Cogible* Player::getObjCogido(){return objCogido;}
Cogible* Player::getObjPuedoCoger(){return objPuedoCoger;}
void Player::setSaltando(bool aux){saltando = aux;}
void Player::setDobleSaltando(bool aux){dobleSaltando = aux;}
void Player::setCogiendo(bool aux){cogiendo = aux;}
void Player::setPuedoCoger(bool aux){puedoCoger = aux;}
void Player::setObjCogido(Cogible* aux){objCogido = aux;}
void Player::setObjPuedoCoger(Cogible* aux){objPuedoCoger = aux;}
void Player::setNextPos(b2Vec2 pos){teletransportado=true; nextPos = pos;}
void Player::setParaMorir(bool aux){paraMorir = aux;}
int Player::getDireccion(){return direccion;}
char* Player::getIp(){return ip;}
char* Player::getId(){return id;}
int Player::getEstado(){return estado;}
char* Player::getServerPort(){return serverPort;}
char* Player::getClientPort(){return clientPort;}
void Player::setIp(char aux[]){strncpy(ip, aux, sizeof(ip));}
void Player::setId(char aux[]){strncpy(id, aux, sizeof(id));}
