#include "Pathfinding/Nodo.h"
#include "MyContactListener.h"
#include "Teleport.h"
#include "Cogible.h"
#include "Metralla.h"
#include "Spawner.h"
#include "Muelle.h"
#include "Player.h"
#include "Bala.h"
#include "Bot.h"

MyContactListener::MyContactListener(){
    //World::Inst()  = World::Inst();
}
void MyContactListener::BeginContact(b2Contact* contact){
    this->contact = contact;
    unsigned long A = (unsigned long)contact->GetFixtureA()->GetUserData();
    unsigned long B = (unsigned long)contact->GetFixtureB()->GetUserData();
    const Contact2Method * it = beginContact;
    while(it->A != 0){
        if((it->A == A && it->B == B)
        || (it->A == B && it->B == A)){
            (this->*it->Contact2Method::p)();
            break;
        }
        it++;
    }
}
void MyContactListener::EndContact(b2Contact* contact){
    this->contact = contact;
    unsigned long A = (unsigned long)contact->GetFixtureA()->GetUserData();
    unsigned long B = (unsigned long)contact->GetFixtureB()->GetUserData();
    const Contact2Method * it = endContact;
    while(it->A != 0){
        if((it->A == A && it->B == B)
        || (it->A == B && it->B == A)){
            (this->*it->Contact2Method::p)();
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
    for(unsigned int i = 0; i < World::Inst()->GetTeleports().size(); ++i){
        if(World::Inst()->GetTeleports().at(i)){
            if(tp->getTeleportPartnerId() == World::Inst()->GetTeleports().at(i)->getTeleportId()){
                GetPlayer()->setNextPos(World::Inst()->GetTeleports().at(i)->getPosition());
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
    GetBala()->setDestruir(true);
}
void MyContactListener::PlayerMetralla(){
    GetPlayer()->setParaMorir(true);
}

void MyContactListener::PlayerNodo(){
    Bot* bot = dynamic_cast<Bot*>(GetPlayer());
    if(bot){
        Nodo* nodo = GetNodo();
        if(nodo && bot->getMuerto() == false){
            bot->colisionConNodo(nodo->getNumero());
        }
    }
}
void MyContactListener::TeleportBala(){Teleport* tp = GetTeleport();
    for(unsigned int i = 0; i < World::Inst()->GetTeleports().size(); ++i){
        if(World::Inst()->GetTeleports().at(i)){
            if(tp->getTeleportPartnerId() == World::Inst()->GetTeleports().at(i)->getTeleportId()){
                GetBala()->setNextPos(World::Inst()->GetTeleports().at(i)->getPosition());
                return;
            }
        }
    }
}
void MyContactListener::TeleportCogible(){
    Teleport* tp = GetTeleport();
    if(GetPlayer() == NULL){
        for(unsigned int i = 0; i < World::Inst()->GetTeleports().size(); ++i){
            if(World::Inst()->GetTeleports().at(i)){
                if(tp->getTeleportPartnerId() == World::Inst()->GetTeleports().at(i)->getTeleportId()){
                    GetCogible()->setNextPos(World::Inst()->GetTeleports().at(i)->getPosition());
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
    for(unsigned int i = 0; i < World::Inst()->GetPlayers().size(); ++i){
        if(World::Inst()->GetPlayers().at(i)->GetId() ==  (int)contact->GetFixtureA()->GetBody()->GetUserData()
        || World::Inst()->GetPlayers().at(i)->GetId() ==  (int)contact->GetFixtureB()->GetBody()->GetUserData() ){
            return World::Inst()->GetPlayers().at(i);
        }
    }
    return NULL;
}
Cogible* MyContactListener::GetCogible(){
    for(unsigned int i = 0; i < World::Inst()->GetCogibles().size(); ++i){
        if(World::Inst()->GetCogibles().at(i)->GetId() ==  (int)contact->GetFixtureA()->GetBody()->GetUserData()
        || World::Inst()->GetCogibles().at(i)->GetId() ==  (int)contact->GetFixtureB()->GetBody()->GetUserData() ){
            return World::Inst()->GetCogibles().at(i);
        }
    }
    return NULL;
}
Muelle* MyContactListener::GetMuelle(){
    for(unsigned int i = 0; i < World::Inst()->GetMuelles().size(); ++i){
        if(World::Inst()->GetMuelles().at(i)->GetId() ==  (int)contact->GetFixtureA()->GetBody()->GetUserData()
        || World::Inst()->GetMuelles().at(i)->GetId() ==  (int)contact->GetFixtureB()->GetBody()->GetUserData() ){
            return World::Inst()->GetMuelles().at(i);
        }
    }
    return NULL;
}
Teleport* MyContactListener::GetTeleport(){
    for(unsigned int i = 0; i < World::Inst()->GetTeleports().size(); ++i){
        if(World::Inst()->GetTeleports().at(i)->GetId() ==  (int)contact->GetFixtureA()->GetBody()->GetUserData()
        || World::Inst()->GetTeleports().at(i)->GetId() ==  (int)contact->GetFixtureB()->GetBody()->GetUserData() ){
            return World::Inst()->GetTeleports().at(i);
        }
    }
    return NULL;
}
Bala* MyContactListener::GetBala(){
    for(unsigned int i = 0; i < World::Inst()->GetBalas().size(); ++i){
        if(World::Inst()->GetBalas().at(i)->GetId() ==  (int)contact->GetFixtureA()->GetBody()->GetUserData()
        || World::Inst()->GetBalas().at(i)->GetId() ==  (int)contact->GetFixtureB()->GetBody()->GetUserData() ){
            return World::Inst()->GetBalas().at(i);
        }
    }
    return NULL;
}
Nodo* MyContactListener::GetNodo(){
    for(unsigned int i = 0; i < World::Inst()->GetNodos().size(); ++i){
        if(World::Inst()->GetNodos().at(i)->GetId() ==  (int)contact->GetFixtureA()->GetBody()->GetUserData()
        || World::Inst()->GetNodos().at(i)->GetId() ==  (int)contact->GetFixtureB()->GetBody()->GetUserData() ){
            return World::Inst()->GetNodos().at(i);
        }
    }
    return NULL;
}
Metralla* MyContactListener::GetMetralla(){
    for(unsigned int i = 0; i < World::Inst()->GetMetrallas().size(); ++i){
        if(World::Inst()->GetMetrallas().at(i)->GetId() ==  (int)contact->GetFixtureA()->GetBody()->GetUserData()
        || World::Inst()->GetMetrallas().at(i)->GetId() ==  (int)contact->GetFixtureB()->GetBody()->GetUserData() ){
            return World::Inst()->GetMetrallas().at(i);
        }
    }
    return NULL;
}
