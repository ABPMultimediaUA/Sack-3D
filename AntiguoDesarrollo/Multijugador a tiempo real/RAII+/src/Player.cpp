
#include "Player.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

#define LEVANTADO        1
#define MUERTO_DORMIDO   2
#define AGACHADO         3
#define PLAYER           10
#define PIESPLAYER       100


Player::Player(b2Vec2 pos, int numMando):Cogible(pos),mando(numMando){
    estado = LEVANTADO;
    direccion = 0;
    strncpy(id, "", sizeof(id));
    tam = irr::core::vector3df(.7f, 1.8f,.7f);
    node = IrrManager::Instance()->addCubeSceneNode(tam,irr::video::SColor(255, 255, 124, 150));
    node->setPosition(irr::core::vector3df(pos.x,pos.y,0));
    node->setMaterialTexture(0,IrrManager::Instance()->getDriver()->getTexture("media/texture.jpg"));
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x,pos.y);
    bodyDef.type = b2_dynamicBody;
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    body->SetFixedRotation(true);
    InicializeFixtures(LEVANTADO);
    eventReceiver = IrrManager::Instance()->getEventReciever();
    node->addShadowVolumeSceneNode();
}
void Player::InicializeFixtures(int mode){
    switch(mode){
        case LEVANTADO:{
            b2FixtureDef fixtureDef;
            b2PolygonShape polyShape;
            body->SetAngularVelocity(0);
            body->SetTransform( body->GetPosition(),0);
            body->SetFixedRotation(true);
            body->ApplyLinearImpulse(b2Vec2(0,5.0f),b2Vec2(0,0));
            polyShape.SetAsBox(tam.X/2.0f,tam.Y/2.0f);
            fixtureDef.shape = &polyShape;
            fixtureDef.friction = 0;
            fixtureDef.restitution  = 0;
            fixtureDef.density  = 10.0f;
            b2Fixture* fixture = body->CreateFixture(&fixtureDef);
            fixture->SetUserData((void*)PLAYER);
            polyShape.SetAsBox(tam.X/4,tam.Y/4,b2Vec2(0,-tam.Y/2), 0);
            fixtureDef.isSensor = true;
            b2Fixture* sensorFixture = body->CreateFixture(&fixtureDef);
            sensorFixture->SetUserData((void*)PIESPLAYER);
        break;}
        case MUERTO_DORMIDO:{
            b2FixtureDef fixtureDef;
            b2FixtureDef fixtureDef2;
            b2CircleShape circleShape1;
            b2CircleShape circleShape2;
            friction = 1.f; restitution = 0.5f; density = 1;
            body->SetFixedRotation(false);
            circleShape1.m_p.Set(0,-0.5f);
            circleShape2.m_p.Set(0,0.5f);
            circleShape1.m_radius = (tam.X)/2;
            circleShape2.m_radius = (tam.X)/2;
            fixtureDef.shape = &circleShape1;
            fixtureDef.friction =friction;
            fixtureDef.restitution  = restitution;
            fixtureDef.density  = density;
            personFixture = body->CreateFixture(&fixtureDef);
            personFixture->SetUserData((void*)PLAYER);
            fixtureDef2.shape = &circleShape2;
            fixtureDef2.friction = friction;
            fixtureDef2.restitution  =restitution;
            fixtureDef2.density  = density;
            b2Fixture* personFixture2 = body->CreateFixture(&fixtureDef2);
            personFixture2->SetUserData((void*)PLAYER);
            circleShape1.m_radius = 1;
            fixtureDef2.isSensor = true;
            fixtureDef2.filter.maskBits = 1;
            fixtureDef2.filter.categoryBits = 2;
            b2Fixture* areaFixure = body->CreateFixture(&fixtureDef2);
            areaFixure->SetUserData((void*)SENSOR);
            body->SetTransform( body->GetPosition(),0);
            body->SetAngularVelocity(0);
            body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x,body->GetLinearVelocity().y+5));
            if(body->GetLinearVelocity().x > 0 )body->ApplyAngularImpulse(-0.5f);
            else body->ApplyAngularImpulse(0.5f);
        break;}
        case AGACHADO:{
        break;}
    }
}
void Player::DestroyFixtures(){
    for (b2Fixture* f = body->GetFixtureList(); f;){
        b2Fixture* fixtureToDestroy = f;
        f = f->GetNext();
        body->DestroyFixture( fixtureToDestroy );
    }
}
void Player::actualiza(){
    if(paraMorir)morir();
    if(cogido)
        node->setPosition(irr::core::vector3df(body->GetPosition().x+((.5f)*dir),body->GetPosition().y,0));
    else
        node->setPosition(irr::core::vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(irr::core::vector3df(0,0,body->GetAngle()*RADTOGRAD));
    mover();
    if(teletransportado)teletransportar();
}
void Player::mover(){
    if(muerto || fingiendoMuerte)
        return;
    dir = 0;
    if(mando == 1){
        if(eventReceiver->IsKeyDown(irr::KEY_KEY_A)){direccion = dir = -1;}
        else if(eventReceiver->IsKeyDown(irr::KEY_KEY_D)){direccion = dir = 1;}
    }
    body->SetLinearVelocity(b2Vec2 (dir*vel, body->GetLinearVelocity().y));
    if(cogiendo) objCogido->setDireccion(dir);
}
void Player::saltar(){
    if(muerto || fingiendoMuerte)
        return;
    if(!saltando){
        b2Vec2 velV = body->GetLinearVelocity();
        velV.y = salto;
        body->SetLinearVelocity(velV);
    }
    else if(!dobleSaltando){
        b2Vec2 velV = body->GetLinearVelocity();
        velV.y = salto*3/4;
        body->SetLinearVelocity(velV);
        dobleSaltando = true;
    }
}
void Player::fingirMuerte(){
    if(cogiendo) Soltar();
    if(muerto)
        return;
    DestroyFixtures();
    if(!fingiendoMuerte){
        fingiendoMuerte = true;
        estado = MUERTO_DORMIDO;
        InicializeFixtures(MUERTO_DORMIDO);

    }
    else{
        fingiendoMuerte = false;
        estado = LEVANTADO;
        InicializeFixtures(LEVANTADO);
    }
}
void Player::morir(){
    paraMorir = false;
    if(cogiendo) Soltar();
    DestroyFixtures();
        estado = MUERTO_DORMIDO;
    InicializeFixtures(MUERTO_DORMIDO);
    muerto = true;
}
void Player::CogerTirar(){
    if(puedoCoger && !cogiendo){
        objCogido = objPuedoCoger;
        objCogido->setCogido(true);
        b2RevoluteJointDef jointDef;
        jointDef.bodyA = body;
        jointDef.bodyB = objPuedoCoger->getBody();
        jointDef.localAnchorA.Set(0,0);
        jointDef.localAnchorB.Set(0,0);
        joint = (b2RevoluteJoint*)PhysicWorld::Instance()->GetWorld()->CreateJoint(&jointDef);
        joint->EnableMotor(true);
        cogiendo = true;
        cliente->enviarCogido(objCogido->getIdCogible());
        std::cout<<"COGIBLE n "<<objCogido->getIdCogible()<<std::endl;
    }
    else if(cogiendo){
        Soltar();
    }
}
void Player::recibeImpulso(float fuerza){
    saltando = true;
    b2Vec2 velV = body->GetLinearVelocity();
    velV.y = fuerza;
    body->SetLinearVelocity(velV);
}
void Player::teletransportar(){
    teletransportado = false;
    if(dir != 0) nextPos.x += (dir*2);
    else nextPos.x += 1.5f;
    velActual = body->GetLinearVelocity();
    body->SetTransform(b2Vec2(nextPos.x,nextPos.y), body->GetAngle());
    body->SetLinearVelocity(velActual);
}
void Player::Soltar(){
    PhysicWorld::Instance()->GetWorld()->DestroyJoint(joint);
    b2Vec2 velP = body->GetLinearVelocity();
    velP.x/=20;
    velP.y +=1.f;
    objCogido->getBody()->ApplyLinearImpulse( velP, objCogido->getBody()->GetLocalCenter());
    cogiendo = false;
    puedoCoger = false;
    objCogido->setCogido(false);
}
void Player::usar(){
    if(Usable* usable = dynamic_cast<Usable*>(objCogido))usable->usar();
}

char* Player::getServerPort(){return serverPort;}
char* Player::getClientPort(){return clientPort;}
char* Player::getIp(){return ip;}
char* Player::getId(){return id;}
int  Player::getDireccion(){return direccion;}
void Player::setClientPort(char aux[]){strncpy(clientPort, aux, sizeof(clientPort));}
void Player::setServerPort(char aux[]){strncpy(serverPort, aux, sizeof(serverPort));}
void Player::setIp(char aux[]){strncpy(ip, aux, sizeof(ip));}
void Player::setId(char aux[]){
    strncpy(id, aux, sizeof(id));
}


