
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

    //Player esta sobre algo.
    if(	   (unsigned long)fixtureUserDataA == PIESPLAYER
		|| (unsigned long)fixtureUserDataB == PIESPLAYER){
        if(PhysicWorld::Instance()->getPlayer(1)->getBody() == contact->GetFixtureA()->GetBody()){
            PhysicWorld::Instance()->getPlayer(1)->setSaltando(false);
            PhysicWorld::Instance()->getPlayer(1)->setDobleSaltando(false);
        }else if(PhysicWorld::Instance()->getPlayer(2)->getBody() == contact->GetFixtureA()->GetBody()){
            PhysicWorld::Instance()->getPlayer(2)->setSaltando(false);
            PhysicWorld::Instance()->getPlayer(2)->setDobleSaltando(false);
        }
	}

    //PLAYER ENTRA EN AREA DE ALGO COGIBLE
    if(((unsigned long)fixtureUserDataB == SENSORARMA && (unsigned long)fixtureUserDataA==PLAYER)
     ||((unsigned long)fixtureUserDataA == SENSORARMA && (unsigned long)fixtureUserDataB==PLAYER)){
        for (std::vector<Cogible*>::iterator it2 = PhysicWorld::Instance()->GetCogibles()->begin(); it2 != PhysicWorld::Instance()->GetCogibles()->end(); it2++){
            if(((*it2)->getBody() == contact->GetFixtureB()->GetBody())
             ||((*it2)->getBody() == contact->GetFixtureA()->GetBody())){
                if((contact->GetFixtureA()->GetBody() == PhysicWorld::Instance()->getPlayer(1)->getBody())
                 ||(contact->GetFixtureB()->GetBody() == PhysicWorld::Instance()->getPlayer(1)->getBody())){
                    PhysicWorld::Instance()->getPlayer(1)->setObjPuedoCoger((*it2));
                    PhysicWorld::Instance()->getPlayer(1)->setPuedoCoger(true);
                }else if((contact->GetFixtureA()->GetBody() == PhysicWorld::Instance()->getPlayer(2)->getBody())
                       ||(contact->GetFixtureB()->GetBody() == PhysicWorld::Instance()->getPlayer(2)->getBody())){
                    PhysicWorld::Instance()->getPlayer(2)->setObjPuedoCoger((*it2));
                    PhysicWorld::Instance()->getPlayer(2)->setPuedoCoger(true);
                }
            }
        }
    }
    //Player entra en contacto con un muelle
		if(   ((unsigned long)fixtureUserDataA == PLAYER && (unsigned long)fixtureUserDataB == MUELLE)
		    ||((unsigned long)fixtureUserDataB == PLAYER && (unsigned long)fixtureUserDataA == MUELLE)){
	    for (std::vector<Muelle*>::iterator it2 = PhysicWorld::Instance()->GetMuelles()->begin(); it2 != PhysicWorld::Instance()->GetMuelles()->end(); it2++){
            if((*it2)->getBody() == contact->GetFixtureB()->GetBody() || (*it2)->getBody() == contact->GetFixtureA()->GetBody()){
                if(contact->GetFixtureB()->GetBody() == PhysicWorld::Instance()->getPlayer(1)->getBody()
                || contact->GetFixtureA()->GetBody() == PhysicWorld::Instance()->getPlayer(1)->getBody()){
                    PhysicWorld::Instance()->getPlayer(1)->recibeImpulso((*it2)->getFuerza());
                }else if(contact->GetFixtureB()->GetBody() == PhysicWorld::Instance()->getPlayer(2)->getBody()
                      || contact->GetFixtureA()->GetBody() == PhysicWorld::Instance()->getPlayer(2)->getBody()){
                    PhysicWorld::Instance()->getPlayer(2)->recibeImpulso((*it2)->getFuerza());
                }
            }
        }
	}

	//Player entra en contacto con un teletransporte
	if(   ((unsigned long)fixtureUserDataA == PLAYER && (unsigned long)fixtureUserDataB == TELETRANSPORTE)
        ||((unsigned long)fixtureUserDataB == PLAYER && (unsigned long)fixtureUserDataA == TELETRANSPORTE)){
	    for (std::vector<Teleport*>::iterator it2 = PhysicWorld::Instance()->GetTeletransportes()->begin(); it2 != PhysicWorld::Instance()->GetTeletransportes()->end(); it2++){
            if((*it2)->getBody() == contact->GetFixtureB()->GetBody() || (*it2)->getBody() == contact->GetFixtureA()->GetBody()){
                for (std::vector<Teleport*>::iterator it3 = PhysicWorld::Instance()->GetTeletransportes()->begin(); it3 != PhysicWorld::Instance()->GetTeletransportes()->end(); it3++){
                    if((*it2)->getTeleportPartnerId() == (*it3)->getTeleportId()){
                        if(contact->GetFixtureB()->GetBody() == PhysicWorld::Instance()->getPlayer(1)->getBody()
                        || contact->GetFixtureA()->GetBody() == PhysicWorld::Instance()->getPlayer(1)->getBody()){
                            PhysicWorld::Instance()->getPlayer(1)->setNextPos((*it3)->getBody()->GetPosition());
                        }else if(contact->GetFixtureB()->GetBody() == PhysicWorld::Instance()->getPlayer(2)->getBody()
                              || contact->GetFixtureA()->GetBody() == PhysicWorld::Instance()->getPlayer(2)->getBody()){
                            PhysicWorld::Instance()->getPlayer(2)->setNextPos((*it3)->getBody()->GetPosition());
                        }
                    }
                }
            }
        }
	}

	//Player entra en contacto con un elemento hostil
	if(((unsigned long)fixtureUserDataA == PLAYER && (unsigned long)fixtureUserDataB == BALA)
     ||((unsigned long)fixtureUserDataB == PLAYER && (unsigned long)fixtureUserDataA == BALA)){
            if(contact->GetFixtureA()->GetBody() == PhysicWorld::Instance()->getPlayer(1)->getBody()
            || contact->GetFixtureB()->GetBody() == PhysicWorld::Instance()->getPlayer(1)->getBody()){
                PhysicWorld::Instance()->getPlayer(1)->setParaMorir(true);
            }else if(contact->GetFixtureA()->GetBody() == PhysicWorld::Instance()->getPlayer(2)->getBody()
                  || contact->GetFixtureB()->GetBody() == PhysicWorld::Instance()->getPlayer(2)->getBody()){
                PhysicWorld::Instance()->getPlayer(2)->setParaMorir(true);
            }
	}



	//Bala entra en contacto con un teletransporte
	if(   ((unsigned long)fixtureUserDataA == BALA && (unsigned long)fixtureUserDataB == TELETRANSPORTE)
	    ||((unsigned long)fixtureUserDataB == BALA && (unsigned long)fixtureUserDataA == TELETRANSPORTE)){

	    for (std::vector<Teleport*>::iterator it2 = PhysicWorld::Instance()->GetTeletransportes()->begin(); it2 != PhysicWorld::Instance()->GetTeletransportes()->end(); it2++){
            if((*it2)->getBody() == contact->GetFixtureB()->GetBody() || (*it2)->getBody() == contact->GetFixtureA()->GetBody()){
                for (std::vector<Teleport*>::iterator it3 = PhysicWorld::Instance()->GetTeletransportes()->begin(); it3 != PhysicWorld::Instance()->GetTeletransportes()->end(); it3++){
                    if((*it2)->getTeleportPartnerId() == (*it3)->getTeleportId()){
                        for (std::vector<Bala*>::iterator it4 = PhysicWorld::Instance()->GetBalas()->begin(); it4 != PhysicWorld::Instance()->GetBalas()->end(); it4++){
                            if((*it4)->getBody() == contact->GetFixtureB()->GetBody() || (*it4)->getBody() == contact->GetFixtureA()->GetBody()){
                                (*it4)->setNextPos((*it3)->getBody()->GetPosition());
                            }
                        }
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
	if(   (unsigned long) fixtureUserDataA== PIESPLAYER
		||(unsigned long) fixtureUserDataB== PIESPLAYER){
	    if(PhysicWorld::Instance()->getPlayer(1)->getBody() == contact->GetFixtureA()->GetBody()){
            PhysicWorld::Instance()->getPlayer(1)->setSaltando(true);
        }else if(PhysicWorld::Instance()->getPlayer(2)->getBody() == contact->GetFixtureA()->GetBody()){
            PhysicWorld::Instance()->getPlayer(2)->setSaltando(true);
        }
	}

	//Player sale de area cogible de Pistola.
	if(   ((unsigned long)fixtureUserDataA== PLAYER && (unsigned long)fixtureUserDataB== SENSORARMA)
		||((unsigned long)fixtureUserDataB == PLAYER && (unsigned long)fixtureUserDataA == SENSORARMA)){
	    if(contact->GetFixtureA()->GetBody() == PhysicWorld::Instance()->getPlayer(1)->getBody()
        || contact->GetFixtureB()->GetBody() == PhysicWorld::Instance()->getPlayer(1)->getBody())
            PhysicWorld::Instance()->getPlayer(1)->setPuedoCoger(false);
        else if(contact->GetFixtureA()->GetBody() == PhysicWorld::Instance()->getPlayer(2)->getBody()
        || contact->GetFixtureB()->GetBody() == PhysicWorld::Instance()->getPlayer(2)->getBody())
            PhysicWorld::Instance()->getPlayer(2)->setPuedoCoger(false);
	}
}

