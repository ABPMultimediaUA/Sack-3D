
#include "MyContactListener.h"
#include "PhysicWorld.h"

#define PLAYER 10
#define PIESPLAYER 100
#define ARMA 30
#define SENSORARMA 35
#define BALA 40
#define CUBOS 45
#define MUELLE 50
#define TELETRANSPORTE 60
#define HOSTILES 70

MyContactListener::MyContactListener(){}

void MyContactListener::BeginContact(b2Contact* contact){
	 void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
     void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

    //LOS PIES DEL PLAYER TOCAN ALGO POR LO TANTO PUEDE VOLVER A SALTAR
    if(	   (unsigned long)fixtureUserDataA == PIESPLAYER
		|| (unsigned long)fixtureUserDataB == PIESPLAYER){
        for(int i = 0; i < MAX_NUM_PLAYER; ++i){
            if(PhysicWorld::Instance()->GetPlayers()[i].Get()){
                if(PhysicWorld::Instance()->GetPlayers()[i].Get()->getBody() ==  contact->GetFixtureA()->GetBody()
                || PhysicWorld::Instance()->GetPlayers()[i].Get()->getBody() ==  contact->GetFixtureB()->GetBody() ){
                    PhysicWorld::Instance()->GetPlayers()[i].Get()->setSaltando(false);
                    PhysicWorld::Instance()->GetPlayers()[i].Get()->setDobleSaltando(false);
                    return;
                }
            }
        }
	}
    if(((unsigned long)fixtureUserDataA==PLAYER)
     ||((unsigned long)fixtureUserDataB==PLAYER)){
         for(int i = 0; i < MAX_NUM_PLAYER; ++i){
            if(PhysicWorld::Instance()->GetPlayers()[i].Get()){
                if(PhysicWorld::Instance()->GetPlayers()[i].Get()->getBody() ==  contact->GetFixtureA()->GetBody()
                || PhysicWorld::Instance()->GetPlayers()[i].Get()->getBody() ==  contact->GetFixtureB()->GetBody() ){
                    //PLAYER HA TOCADO ARMA
                    if(((unsigned long)fixtureUserDataB == SENSORARMA)
                     ||((unsigned long)fixtureUserDataA == SENSORARMA)){
                        for (std::vector<Cogible*>::iterator it2 = PhysicWorld::Instance()->GetCogibles()->begin(); it2 != PhysicWorld::Instance()->GetCogibles()->end(); it2++){
                            if(((*it2)->getBody() == contact->GetFixtureB()->GetBody())
                             ||((*it2)->getBody() == contact->GetFixtureA()->GetBody())){
                                PhysicWorld::Instance()->GetPlayers()[i].Get()->setObjPuedoCoger((*it2));
                                PhysicWorld::Instance()->GetPlayers()[i].Get()->setPuedoCoger(true);
                                return;
                            }
                        }
                    }
                    //PLAYER HA TOCADO MUELLE
            		if(((unsigned long)fixtureUserDataB == MUELLE)
            		 ||((unsigned long)fixtureUserDataA == MUELLE)){
                        for(int j = 0; j < MAX_NUM_MUELLE; ++j){
                            if(PhysicWorld::Instance()->GetMuelles()[j].Get()){
                                if(PhysicWorld::Instance()->GetMuelles()[j].Get()->getBody() == contact->GetFixtureB()->GetBody()
                                || PhysicWorld::Instance()->GetMuelles()[j].Get()->getBody() == contact->GetFixtureA()->GetBody()){
                                    PhysicWorld::Instance()->GetPlayers()[i].Get()->recibeImpulso(PhysicWorld::Instance()->GetMuelles()[j].Get()->getFuerza());
                                    return;
                                }
                            }
                        }
                	}
                	//PLAYER TOCA TELEPORT
                	if(((unsigned long)fixtureUserDataB == TELETRANSPORTE)
                     ||((unsigned long)fixtureUserDataA == TELETRANSPORTE)){
                        for(int k = 0; k < MAX_NUM_TELEPORT; ++k){
                            if(PhysicWorld::Instance()->GetTeletransportes()[k].Get()){
                                if(PhysicWorld::Instance()->GetTeletransportes()[k].Get()->getBody() == contact->GetFixtureB()->GetBody() 
                                 ||PhysicWorld::Instance()->GetTeletransportes()[k].Get()->getBody() == contact->GetFixtureA()->GetBody()){
                                    for(int j = 0; j < MAX_NUM_TELEPORT; ++j){
                                        if(PhysicWorld::Instance()->GetTeletransportes()[j].Get()){
                                            if(PhysicWorld::Instance()->GetTeletransportes()[k].Get()->getTeleportPartnerId() == PhysicWorld::Instance()->GetTeletransportes()[j].Get()->getTeleportId()){
                                                PhysicWorld::Instance()->GetPlayers()[i].Get()->setNextPos(PhysicWorld::Instance()->GetTeletransportes()[j].Get()->getBody()->GetPosition());
                                                return;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                	//PLAYER TOCA BALA
                	if(((unsigned long)fixtureUserDataB == BALA)
                     ||((unsigned long)fixtureUserDataA == BALA)){
                        PhysicWorld::Instance()->GetPlayers()[i].Get()->setParaMorir(true);
                        return;
                	}
                }
            }
        }    
    }
}

void MyContactListener::EndContact(b2Contact* contact){
    void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
    void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

    //Player deja de estar sobre algo
	if((unsigned long)fixtureUserDataA == PIESPLAYER
     ||(unsigned long)fixtureUserDataB == PIESPLAYER){
        for(int i = 0; i < MAX_NUM_PLAYER; ++i){
            if(PhysicWorld::Instance()->GetPlayers()[i].Get()){
                if(PhysicWorld::Instance()->GetPlayers()[i].Get()->getBody() ==  contact->GetFixtureA()->GetBody()
                || PhysicWorld::Instance()->GetPlayers()[i].Get()->getBody() ==  contact->GetFixtureB()->GetBody() ){
                    PhysicWorld::Instance()->GetPlayers()[i].Get()->setSaltando(true);
                    return;
                }
            }
        }
    }

	//Player sale de area cogible de Pistola.
	if(   ((unsigned long)fixtureUserDataA== PLAYER && (unsigned long)fixtureUserDataB== SENSORARMA)
		||((unsigned long)fixtureUserDataB == PLAYER && (unsigned long)fixtureUserDataA == SENSORARMA)){
	    if(contact->GetFixtureA()->GetBody() == PhysicWorld::Instance()->getPlayer(1)->getBody()
        || contact->GetFixtureB()->GetBody() == PhysicWorld::Instance()->getPlayer(1)->getBody()){
            PhysicWorld::Instance()->getPlayer(1)->setPuedoCoger(false);
            return;
        }
	}
}

