#include "PhysicBody/PBDeadPlayer.h"
#include "PhysicBody/PBAlivePlayer.h"
#include "PhysicBody/PBCotton.h"

#include "MyEventReceiver.h"
#include "Particle.h"
#include "Player.h"
#include "Usable.h"
#include "Client.h"
#include "World.h"
#include "Granada.h"

Player::Player(b2Vec2 pos, char *texture, int numMando)
:Cogible(new PBAlivePlayer,NULL,pos,glm::vec3(.07f, 0.15f,.07f),"BearEngine/res/oso.obj",texture),mando(numMando){
    time2Animation = SDL_GetTicks();
    m_pClient = Client::Inst();
    boton_saltar = false;
    boton_coger = false;
    boton_muerteBots = false;
    boton_muerto = false;
    vel = 3.0f;
    moviendoA = 0;
    moviendo = 0;
    salto = 7.0f;
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
    lastDir = 0;
    strncpy(id, m_pClient->getIdCliente(), sizeof(id));
    m_gameObject.AddModel("BearEngine/res/Correr/osoCorrer1.obj");
    m_gameObject.AddModel("BearEngine/res/Correr/osoCorrer2.obj");
    m_gameObject.AddModel("BearEngine/res/Correr/osoCorrer3.obj");
    m_gameObject.AddModel("BearEngine/res/Correr/osoCorrer4.obj");
    m_gameObject.AddModel("BearEngine/res/Correr/osoCorrer5.obj");
    m_gameObject.AddModel("BearEngine/res/Correr/osoCorrer1.obj");
}
 Player::~Player(){
}
void Player::actualiza(MyEventReceiver *events){
    if(!muerto  && SDL_GetTicks()-time2Animation>100){
        m_gameObject.NextFrame();
        time2Animation = SDL_GetTicks();
    }
    if(m_gameObject.GetLinearVelocity().x <= 1 && m_gameObject.GetLinearVelocity().x >= -1){
        m_gameObject.ResetAnimacion();
    }
    if(events){
        if(!boton_saltar && events->IsKeyDown(SDLK_SPACE)){
            boton_saltar = true;
            saltar();
        }
        else if( boton_saltar && !events->IsKeyDown(SDLK_SPACE)){
            boton_saltar = false;
        }
        if(!boton_coger && events->IsKeyDown(SDLK_e)){
            boton_coger = true;
            CogerTirar();
        }
        else if( boton_coger && !events->IsKeyDown(SDLK_e)){
            boton_coger = false;
        }
        /////////////////////////////MOD MUERTE BOTS HAHAHA/////////////////////
        if(!boton_muerteBots && events->IsKeyDown(SDLK_k)){
            boton_muerteBots = true;
            std::vector<Player*> botsMuerte;
            botsMuerte = World::Inst()->GetPlayers();
            for(int i = 1; i<4;i++){
                if(botsMuerte.at(i)->getMuerto() == false)
                    botsMuerte.at(i)->morir();
            }
        }
        else if( boton_muerteBots && !events->IsKeyDown(SDLK_k)){
            boton_muerteBots = false;
        }
        ///////////////////////////////////////////////////////////////////////

        if(!boton_muerto && events->IsKeyDown(SDLK_q)){
            boton_muerto = true;
            fingirMuerte();
        }
        else if( boton_muerto && !events->IsKeyDown(SDLK_q)){
            boton_muerto = false;
        }
         if(events->IsKeyDown(SDLK_RETURN)){
            usar();
        }
    }
    if(teletransportado)teletransportar();
    if(!muerto && paraMorir)morir();
    m_gameObject.Update();
    mover(events);
}
void Player::mover(MyEventReceiver *events){
    if(muerto || fingiendoMuerte)
        return;
    dir = 0;
    int id2 = (*m_pClient->getIdCliente())-'0';
    if(mando == id2){
        if(events && events->IsKeyDown(SDLK_a)){
            moviendo = lastDir = direccion = dir = -1;
        }
        else if(events && events->IsKeyDown(SDLK_d)){
            moviendo = lastDir = direccion = dir = 1;
        }
        else{
                moviendo = 0;
        }
    }
    if(moviendo != moviendoA){
        m_pClient->enviarMoviendo(moviendo, mando);
        moviendoA = moviendo;
    }

    if(lastDir ==  1)       m_gameObject.SetXRotation(0);
    else if(lastDir == -1)  m_gameObject.SetXRotation(180);

    m_gameObject.SetLinearVelocity(b2Vec2 (moviendo*vel, m_gameObject.GetLinearVelocity().y));

    if(cogiendo)
        objCogido->setDireccion(lastDir);
}
void Player::saltar(){
    if(muerto)
        return;
    if(fingiendoMuerte){
        b2Vec2 velV;
        velV.x = 0;
        velV.y = 1;
        m_gameObject.SetLinearVelocity(velV);
        m_gameObject.SetAngularVelocity((rand()%10-5)/1000.f);
        m_pClient->enviarSalto(0);
        return;
    }
    if(!saltando){
        b2Vec2 velV = m_gameObject.GetLinearVelocity();
        velV.y = salto;
        m_gameObject.SetLinearVelocity(velV);
        m_pClient->enviarSalto(1, mando);
    }
    else if(!dobleSaltando && !fingiendoMuerte){
        b2Vec2 velV = m_gameObject.GetLinearVelocity();
        velV.y = salto*3/4;
        m_gameObject.SetLinearVelocity(velV);
        dobleSaltando = true;
        m_pClient->enviarSalto(2, mando);
    }
}
void Player::fingirMuerte(){
    m_pClient->enviarHacerseMuerto(mando);
    if(cogiendo) Soltar();
    if(muerto)
        return;
    if(!fingiendoMuerte){
        fingiendoMuerte = true;
        m_id = m_gameObject.SetMode(new PBDeadPlayer);
        if(direccion > 0 )
            m_gameObject.SetAngularVelocity(-0.001f);
        else
            m_gameObject.SetAngularVelocity(0.001f);
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
        m_pClient->enviarMuerto(mando);
    }
}
void Player::BloodExplosion(){
    b2Vec2 pos = m_gameObject.GetPosition();
    pos.y *= -1;
    pos.x=pos.x/2.0f;
    pos.y=pos.y/2.0f;
    for (int i = 0; i < 50; ++i){
        glm::vec3 tam(0.02f,0.02f,0.02f);
        Particle *cap = m_pWorld->AddParticle(new Particle(new PBCotton(),pos,tam,rand()%300+1000,"BearEngine/res/1.obj","media/Images/sangre.png"));
        b2Vec2 capVel;
        capVel.x = dir*(rand()%10)+2;
        capVel.y =rand()%10-5;
        cap->SetLinearVelocity(capVel);
    }
}
void Player::CogerTirar(){
    if(!muerto && !fingiendoMuerte){
        if(puedoCoger && !cogiendo){
            Usable* usable = dynamic_cast<Usable*>(objPuedoCoger);
            if(usable && usable->getUsos() && !usable->getCogido()){
                if(dynamic_cast<Granada*>(objPuedoCoger)){
                    dynamic_cast<Granada*>(objPuedoCoger)->setCogedor(mando);
                    //std::cout<<"SOY "<<mando<<std::endl;
                }
                objCogido = objPuedoCoger;
                objCogido->setCogido(true);
                objCogido->setDireccion(1);
                m_gameObject.Catch(objCogido->GetId());
                cogiendo = true;
                m_pClient->enviarCogido(objCogido->GetIdc(),mando);
                //std::cout<<"SOY "<<mando<<"y envio id "<<objCogido->GetIdc()<<std::endl;
            }
        }
        else if(cogiendo){
            Soltar();
            m_pClient->enviarCogido(-1, mando);
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
    if(m_gameObject.GetLinearVelocity().x > 0 )objCogido->SetAngularVelocity(-0.01f);
    else objCogido->SetAngularVelocity(0.01f);
    b2Vec2 velP = m_gameObject.GetLinearVelocity();
    velP.x*=2;
    if(velP.y == 0)velP.y = 2;
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
        m_pClient->enviarUsar(mando);
        //std::cout<<"POSPLAYER "<<m_gameObject.GetPosition().x<<" "<<m_gameObject.GetPosition().y<<std::endl;
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
