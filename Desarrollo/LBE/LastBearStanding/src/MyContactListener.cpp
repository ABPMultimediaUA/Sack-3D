#include "MyContactListener.h"
#include "World.h"

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
    std::cout<<"EMPIEZATOCA"<<std::endl;
    Player* player = GetPlayer();
    if(player!=NULL){
    player->setSaltando(false);
    player->setDobleSaltando(false);
    }
    std::cout<<"TOCA"<<std::endl;
}
void MyContactListener::PiesPlayerEnd(){
    std::cout<<"EMPIEZANOTOCA"<<std::endl;
    GetPlayer()->setSaltando(true);
    std::cout<<"NO TOCA"<<std::endl;
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

