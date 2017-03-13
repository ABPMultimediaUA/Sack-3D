#include "MyEventReceiver.h"
#include "Player.h"
#include "Usable.h"
#include "Client.h"
#include "World.h"

Player::Player(b2Vec2 pos, int numMando, irr::video::SColor color)
:Cogible(NULL,pos,irr::core::vector3df(.7f, 1.8f,.7f),color),mando(numMando){
    m_pClient = Client::Inst();
    jointDef  = NULL;
    moviendoA = 0;
    moviendo = 0;
    vel=7;
    salto=15;
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
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x+(m_tam.X/2),-1*(pos.y-(m_tam.Y/2)));
    bodyDef.type = b2_dynamicBody;
    m_pBody  = m_pWorld->GetWorld()->CreateBody(&bodyDef);
    m_pBody->SetFixedRotation(true);
    InicializeFixtures(LEVANTADO);
    eventReceiver = IrrMngr::Inst()->getEventReciever();
}
 Player::~Player(){}
void Player::InicializeFixtures(int mode){
    switch(mode){
        case LEVANTADO:{
            b2FixtureDef fixtureDef;
            b2PolygonShape polyShape;
            m_pBody->SetAngularVelocity(0);
            m_pBody->SetTransform( m_pBody->GetPosition(),0);
            m_pBody->SetFixedRotation(true);
            m_pBody->ApplyLinearImpulse(b2Vec2(0,5.0f),b2Vec2(0,0));
            polyShape.SetAsBox((m_tam.X/2),(m_tam.Y/2));
            fixtureDef.shape = &polyShape;
            fixtureDef.friction = 0;
            fixtureDef.restitution  = 0;
            fixtureDef.density  = 10.0f;
            fixtureDef.filter.categoryBits = M_PLAYER;
            fixtureDef.filter.maskBits = M_BALA|M_SUELO|M_TELEPORT|M_MUELLE|M_COGIBLESENSOR;
            b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
            fixture->SetUserData((void*)DATA_PLAYER);
            polyShape.SetAsBox(m_tam.X/4,m_tam.Y/4,b2Vec2(0,-m_tam.Y/2), 0);
            fixtureDef.isSensor = true;
            b2Fixture* sensorFixture = m_pBody->CreateFixture(&fixtureDef);
            sensorFixture->SetUserData((void*)DATA_PLAYER_PIES);
        break;}
        case MUERTO_DORMIDO:{
            b2FixtureDef fixtureDef;
            b2FixtureDef fixtureDef2;
            b2CircleShape circleShape1;
            b2CircleShape circleShape2;
            friction = .5f; restitution = 0.2f; density = 0.8f;
            m_pBody->SetFixedRotation(false);
            circleShape1.m_p.Set(0,-0.5f);
            circleShape2.m_p.Set(0,0.5f);
            circleShape1.m_radius = (m_tam.X)/2;
            circleShape2.m_radius = (m_tam.X)/2;
            fixtureDef.shape = &circleShape1;
            fixtureDef.friction =friction;
            fixtureDef.restitution  = restitution;
            fixtureDef.density  = density;
            personFixture = m_pBody->CreateFixture(&fixtureDef);
            personFixture->SetUserData((void*)DATA_PLAYER);
            fixtureDef2.shape = &circleShape2;
            fixtureDef2.friction = friction;
            fixtureDef2.restitution  =restitution;
            fixtureDef2.density  = density;
            b2Fixture* personFixture2 = m_pBody->CreateFixture(&fixtureDef2);
            personFixture2->SetUserData((void*)DATA_PLAYER);
            circleShape1.m_radius = 1;
            fixtureDef2.isSensor = true;
            fixtureDef2.filter.maskBits = 1;
            fixtureDef2.filter.categoryBits = 2;
            b2Fixture* areaFixure = m_pBody->CreateFixture(&fixtureDef2);
            areaFixure->SetUserData((void*)DATA_COGIBLE_SENSOR);
            m_pBody->SetTransform( m_pBody->GetPosition(),0);
            m_pBody->SetAngularVelocity(0);
            m_pBody->SetLinearVelocity(b2Vec2(m_pBody->GetLinearVelocity().x,m_pBody->GetLinearVelocity().y+5));
            if(m_pBody->GetLinearVelocity().x > 0 )m_pBody->ApplyAngularImpulse(-0.5f);
            else m_pBody->ApplyAngularImpulse(0.5f);
        break;}
        case AGACHADO:{
        break;}
    }
}
void Player::DestroyFixtures(){
    for (b2Fixture* f = m_pBody->GetFixtureList(); f;){
        b2Fixture* fixtureToDestroy = f;
        f = f->GetNext();
        m_pBody->DestroyFixture( fixtureToDestroy );
    }
}
void Player::actualiza(){
    if(teletransportado)teletransportar();
    if(paraMorir)morir();
    if(cogido) m_pNode->setPosition(irr::core::vector3df(m_pBody->GetPosition().x+((.5f)*dir),m_pBody->GetPosition().y,0));
    else m_pNode->setPosition(irr::core::vector3df(m_pBody->GetPosition().x,m_pBody->GetPosition().y,0));
    m_pNode->setRotation(irr::core::vector3df(0,0,m_pBody->GetAngle()*RADTOGRAD));
    mover();
}
void Player::mover(){

    if(muerto || fingiendoMuerte)
        return;
    dir = 0;
    int id2 = (*m_pClient->getIdCliente())-'0';
    if(mando == id2){
        if(eventReceiver->IsKeyDown(irr::KEY_KEY_A)){moviendo = direccion = dir = -1;}
        else if(eventReceiver->IsKeyDown(irr::KEY_KEY_D)){moviendo = direccion = dir = 1;}
        else{moviendo = 0;}
    }
    if(moviendo != moviendoA){

        std::cout<<"ME MUEVOOOOOOOOO"<<id<<std::endl;
            m_pClient->enviarMoviendo(moviendo);
    moviendoA = moviendo;}
    m_pBody->SetLinearVelocity(b2Vec2 (moviendo*vel, m_pBody->GetLinearVelocity().y));
    if(cogiendo) objCogido->setDireccion(moviendo);
}
void Player::saltar(){
    if(muerto)
        return;
    if(fingiendoMuerte){
        b2Vec2 velV;
        velV.x = 0;
        velV.y = 2;
        m_pBody->SetLinearVelocity(velV);
        m_pBody->ApplyAngularImpulse(rand()%4 - 2);
        return;
    }
    if(!saltando){
        b2Vec2 velV = m_pBody->GetLinearVelocity();
        velV.y = salto;
        m_pBody->SetLinearVelocity(velV);
        m_pClient->enviarSalto(1);
    }
    else if(!dobleSaltando){
        b2Vec2 velV = m_pBody->GetLinearVelocity();
        velV.y = salto*3/4;
        m_pBody->SetLinearVelocity(velV);
        dobleSaltando = true;
        m_pClient->enviarSalto(2);
    }
}
void Player::fingirMuerte(){
    m_pClient->enviarHacerseMuerto();
    if(cogiendo) Soltar();
    if(muerto)
        return;
    DestroyFixtures();
    if(!fingiendoMuerte){
        fingiendoMuerte = true;
        InicializeFixtures(MUERTO_DORMIDO);
    }
    else{
        fingiendoMuerte = false;
        InicializeFixtures(LEVANTADO);
    }
}
void Player::morir(){
    if(!muerto){
        paraMorir = false;
        if(cogiendo) Soltar();
        DestroyFixtures();
        estado = MUERTO_DORMIDO;
        InicializeFixtures(MUERTO_DORMIDO);
        muerto = true;
        m_pClient->enviarMuerto();
    }
}
void Player::CogerTirar(){
    if(puedoCoger && !cogiendo){
        Usable* usable = dynamic_cast<Usable*>(objPuedoCoger);
        if(usable && usable->getUsos()){
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
                m_pClient->enviarCogido(objCogido->getIdCogible());
            }
    }
    else if(cogiendo){
        Soltar();
        m_pClient->enviarCogido(-1);
    }
}
void Player::recibeImpulso(float fuerza){
    saltando = true;
    b2Vec2 velV = m_pBody->GetLinearVelocity();
    velV.y = fuerza;
    m_pBody->SetLinearVelocity(velV);
}
void Player::Soltar(){
    m_pWorld->GetWorld()->DestroyJoint(joint);
    b2Vec2 velP = m_pBody->GetLinearVelocity();
    velP.x/=20;
    velP.y = velP.y/30 +1.f;
    objCogido->getBody()->ApplyLinearImpulse( velP, objCogido->getBody()->GetLocalCenter());
    cogiendo = false;
    puedoCoger = false;
    objCogido->setCogido(false);
    if(m_pBody->GetLinearVelocity().x > 0 )objCogido->getBody()->ApplyAngularImpulse(-2);
    else objCogido->getBody()->ApplyAngularImpulse(2);
    cogiendo =false;
}


void Player::teletransportar(){
    teletransportado = false;
    if(dir != 0) nextPos.x += (dir*2);
    else nextPos.x += 1.5f;
    velActual = m_pBody->GetLinearVelocity();
    m_pBody->SetTransform(b2Vec2(nextPos.x,nextPos.y), m_pBody->GetAngle());
    m_pBody->SetLinearVelocity(velActual);
}
void Player::usar(){
    if(cogiendo)if( Usable* usable = dynamic_cast<Usable*>(objCogido)){
        m_pClient->enviarUsar();
        usable->usar();
    }
}
b2Vec2 Player::getPosition(){return m_pBody->GetPosition();}
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
int Player::getEstado(){return estado;}
char* Player::getId(){return id;}
char* Player::getServerPort(){return serverPort;}
char* Player::getClientPort(){return clientPort;}
void Player::setIp(char aux[]){strncpy(ip, aux, sizeof(ip));}
void Player::setId(char aux[]){strncpy(id, aux, sizeof(id));}
