#include "MyContactListener.h"
#include "Teleport.h"
#include "Cogible.h"
#include "Spawner.h"
#include "Muelle.h"
#include "Player.h"
#include "Bala.h"

MyContactListener::MyContactListener(){}
void MyContactListener::BeginContact(b2Contact* contact){
    this->contact = contact;
    unsigned long A = (unsigned long)contact->GetFixtureA()->GetUserData();
    unsigned long B = (unsigned long)contact->GetFixtureB()->GetUserData();
    const Contact2Func * it = beginContact;
    while(it->A != 0){

        if((it->A == A && it->B == B)
        || (it->A == B && it->B == A)){
            (this->*it->Contact2Func::p)();
            break;
        }
        it++;

    }
}
void MyContactListener::EndContact(b2Contact* contact){
    this->contact = contact;
    unsigned long A = (unsigned long)contact->GetFixtureA()->GetUserData();
    unsigned long B = (unsigned long)contact->GetFixtureB()->GetUserData();
    const Contact2Func * it = endContact;
    while(it->A != 0){
        if((it->A == A && it->B == B)
        || (it->A == B && it->B == A)){
            (this->*it->Contact2Func::p)();
            break;
        }
        it++;
    }
}
void MyContactListener::PiesPlayerBegin(){
    Player* player = GetPlayer();
    player->setSaltando(false);
    player->setDobleSaltando(false);
}
void MyContactListener::PiesPlayerEnd(){
    GetPlayer()->setSaltando(true);
}
void MyContactListener::PlayerMuelle(){
   GetPlayer()->recibeImpulso(GetMuelle()->getFuerza());
}
void MyContactListener::PlayerTeleport(){
    Teleport* tp = GetTeleport();
    for(int i = 0; i < World::Inst()->GetTeleports().size(); ++i){
        if(World::Inst()->GetTeleports().at(i)){
            if(tp->getTeleportPartnerId() == World::Inst()->GetTeleports().at(i)->getTeleportId()){
                GetPlayer()->setNextPos(World::Inst()->GetTeleports().at(i)->getBody()->GetPosition());
                return;
            }
        }
    }
}
void MyContactListener::PlayerCogibleBegin(){
    Player* player = GetPlayer();
    player->setObjPuedoCoger(GetCogible());
    player->setPuedoCoger(true);
}
void MyContactListener::PlayerCogibleEnd(){
    GetPlayer()->setPuedoCoger(false);
}
void MyContactListener::PlayerPincho(){
    GetPlayer()->setParaMorir(true);
}
void MyContactListener::PlayerBala(){
    GetPlayer()->setParaMorir(true);
}
void MyContactListener::TeleportBala(){Teleport* tp = GetTeleport();
    for(int i = 0; i < World::Inst()->GetTeleports().size(); ++i){
        if(World::Inst()->GetTeleports().at(i)){
            if(tp->getTeleportPartnerId() == World::Inst()->GetTeleports().at(i)->getTeleportId()){
                GetBala()->setNextPos(World::Inst()->GetTeleports().at(i)->getBody()->GetPosition());
                return;
            }
        }
    }
}
void MyContactListener::TeleportCogible(){
    Teleport* tp = GetTeleport();
    if(GetPlayer() == NULL){
        for(int i = 0; i < World::Inst()->GetTeleports().size(); ++i){
            if(World::Inst()->GetTeleports().at(i)){
                if(tp->getTeleportPartnerId() == World::Inst()->GetTeleports().at(i)->getTeleportId()){
                    GetCogible()->setNextPos(World::Inst()->GetTeleports().at(i)->getBody()->GetPosition());
                    return;
                }
            }
        }
    }
}
void MyContactListener::BalaBegin(){
    if(GetTeleport() == NULL)
        GetBala()->setDestruir(true);
}
Player* MyContactListener::GetPlayer(){
    for(int i = 0; i < World::Inst()->GetPlayers().size(); ++i){
        if(World::Inst()->GetPlayers().at(i)->getBody() ==  contact->GetFixtureA()->GetBody()
        || World::Inst()->GetPlayers().at(i)->getBody() ==  contact->GetFixtureB()->GetBody() ){
            return World::Inst()->GetPlayers().at(i);
        }
    }
    return NULL;
}
Cogible* MyContactListener::GetCogible(){
    for(int i = 0; i < World::Inst()->GetCogibles().size(); ++i){
        if(World::Inst()->GetCogibles().at(i)->getBody() ==  contact->GetFixtureA()->GetBody()
        || World::Inst()->GetCogibles().at(i)->getBody() ==  contact->GetFixtureB()->GetBody() ){
            return World::Inst()->GetCogibles().at(i);
        }
    }
    return NULL;
}
Muelle* MyContactListener::GetMuelle(){
    for(int i = 0; i < World::Inst()->GetMuelles().size(); ++i){
        if(World::Inst()->GetMuelles().at(i)->getBody() ==  contact->GetFixtureA()->GetBody()
        || World::Inst()->GetMuelles().at(i)->getBody() ==  contact->GetFixtureB()->GetBody() ){
            return World::Inst()->GetMuelles().at(i);
        }
    }
    return NULL;
}
Teleport* MyContactListener::GetTeleport(){
    for(int i = 0; i < World::Inst()->GetTeleports().size(); ++i){
        if(World::Inst()->GetTeleports().at(i)->getBody() ==  contact->GetFixtureA()->GetBody()
        || World::Inst()->GetTeleports().at(i)->getBody() ==  contact->GetFixtureB()->GetBody() ){
            return World::Inst()->GetTeleports().at(i);
        }
    }
    return NULL;
}
Bala* MyContactListener::GetBala(){
    for(int i = 0; i < World::Inst()->GetBalas().size(); ++i){
        if(World::Inst()->GetBalas().at(i)->getBody() ==  contact->GetFixtureA()->GetBody()
        || World::Inst()->GetBalas().at(i)->getBody() ==  contact->GetFixtureB()->GetBody() ){
            return World::Inst()->GetBalas().at(i);
        }
    }
    return NULL;
}
