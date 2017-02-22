#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H

#include "Box2D/Box2D.h"
#include "World.h"
#include <iostream>

class MyContactListener;
struct Contact2Func {
     unsigned long A;
     unsigned long B;
     void (MyContactListener::*p)();
};

class MyContactListener: public b2ContactListener{
    public:
        MyContactListener();
        virtual ~MyContactListener(){}
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PlayerMuelle();
        void PlayerTeleport();
        void PlayerCogibleBegin();
        void PlayerCogibleEnd();
        void PlayerBala();
        void PlayerPincho();
        void TeleportBala();
        void TeleportCogible();
        void PiesPlayerBegin();
        void PiesPlayerEnd();
        void BalaBegin();
    private:
    	const Contact2Func beginContact[10] = {
              { DATA_PLAYER         , DATA_MUELLE         , PlayerMuelle        }
            , { DATA_PLAYER         , DATA_TELEPORT       , PlayerTeleport      }
            , { DATA_PLAYER         , DATA_COGIBLE_SENSOR , PlayerCogibleBegin  }
            , { DATA_PLAYER         , DATA_BALA           , PlayerBala          }
            , { DATA_PLAYER         , DATA_PINCHO         , PlayerPincho        }
            , { DATA_TELEPORT       , DATA_BALA           , TeleportBala        }
            , { DATA_TELEPORT       , DATA_COGIBLE        , TeleportCogible     }
            , { DATA_PLAYER_PIES    , 0                   , PiesPlayerBegin     }
            , { DATA_BALA           , 0                   , BalaBegin           }
            , { 0                   , 0                   , 0                   }
        };
        const Contact2Func endContact[3] = {
              { DATA_PLAYER         , DATA_COGIBLE_SENSOR , PlayerCogibleEnd    }
            , { DATA_PLAYER_PIES    , 0                   , PiesPlayerEnd       }
            , { 0                   , 0                   , 0                   }
        };
        b2Contact* contact;
        Player* GetPlayer(){
            for(int i = 0; i < World::Inst()->GetPlayers().size(); ++i){
                    std::cout<<"ENTROOOMAGNA"<<std::endl;
                if(World::Inst()->GetPlayers().at(i)->getBody() ==  contact->GetFixtureA()->GetBody()
                || World::Inst()->GetPlayers().at(i)->getBody() ==  contact->GetFixtureB()->GetBody() ){
                    std::cout<<"ENTROOO????"<<World::Inst()->GetPlayers().at(i)->getId()<<std::endl;
                    return World::Inst()->GetPlayers().at(i);
                }
            }
            std::cout<<"SALGOOMAGNA"<<std::endl;
            return NULL;
        }
        Cogible* GetCogible(){
            for(int i = 0; i < World::Inst()->GetCogibles().size(); ++i){
                if(World::Inst()->GetCogibles().at(i)->getBody() ==  contact->GetFixtureA()->GetBody()
                || World::Inst()->GetCogibles().at(i)->getBody() ==  contact->GetFixtureB()->GetBody() ){
                    return World::Inst()->GetCogibles().at(i);
                }
            }
            return NULL;
        }
        Muelle* GetMuelle(){
            for(int i = 0; i < World::Inst()->GetMuelles().size(); ++i){
                if(World::Inst()->GetMuelles().at(i)->getBody() ==  contact->GetFixtureA()->GetBody()
                || World::Inst()->GetMuelles().at(i)->getBody() ==  contact->GetFixtureB()->GetBody() ){
                    return World::Inst()->GetMuelles().at(i);
                }
            }
            return NULL;
        }
        Teleport* GetTeleport(){
            for(int i = 0; i < World::Inst()->GetTeleports().size(); ++i){
                if(World::Inst()->GetTeleports().at(i)->getBody() ==  contact->GetFixtureA()->GetBody()
                || World::Inst()->GetTeleports().at(i)->getBody() ==  contact->GetFixtureB()->GetBody() ){
                    return World::Inst()->GetTeleports().at(i);
                }
            }
            return NULL;
        }
        Bala* GetBala(){
            for(int i = 0; i < World::Inst()->GetBalas().size(); ++i){
                if(World::Inst()->GetBalas().at(i)->getBody() ==  contact->GetFixtureA()->GetBody()
                || World::Inst()->GetBalas().at(i)->getBody() ==  contact->GetFixtureB()->GetBody() ){
                    return World::Inst()->GetBalas().at(i);
                }
            }
            return NULL;
        }
};

#endif
