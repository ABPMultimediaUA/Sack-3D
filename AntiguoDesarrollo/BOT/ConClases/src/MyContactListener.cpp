#include "MyContactListener.h"
#include "PhysicWorld.h"

//100->Cubs que se crean con el click
//20->Muelle
MyContactListener::MyContactListener(){}

void MyContactListener::BeginContact(b2Contact* contact){
	 void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
     void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

    //DETECTAR SALTO(JUGADOR-SUELO)
	if((unsigned long)fixtureUserDataA == 100 && (unsigned long)fixtureUserDataB== 20){
	    PhysicWorld::Instance()->getPlayer()->setSaltando(false);
	    PhysicWorld::Instance()->getPlayer()->setDobleSaltando(false);
	}

	if((unsigned long)fixtureUserDataB == 100 && (unsigned long)fixtureUserDataA == 20){
	    PhysicWorld::Instance()->getPlayer()->setSaltando(false);
	    PhysicWorld::Instance()->getPlayer()->setDobleSaltando(false);
	}

    //DETECTAR COGER(JUGADOR-CUBO)
	if((unsigned long)fixtureUserDataA == 100 && (unsigned long)fixtureUserDataB== 30){
	    std::cout<<"Puedes coger cubo"<<std::endl;
	    PhysicWorld::Instance()->getPlayer()->setPuedoCoger(true);
	}

	if((unsigned long)fixtureUserDataB == 100 && (unsigned long)fixtureUserDataA == 30){
	    std::cout<<"Puedes coger cubo"<<std::endl;
	    PhysicWorld::Instance()->getPlayer()->setPuedoCoger(true);
	}

}
void MyContactListener::EndContact(b2Contact* contact){
    void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
    void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

    //DETECTAR SALTO(JUGADOR-SUELO)
	if((unsigned long) fixtureUserDataA== 100 && (unsigned long)fixtureUserDataB== 20){
	    PhysicWorld::Instance()->getPlayer()->setSaltando(true);
	}

	if((unsigned long)fixtureUserDataB == 100 && (unsigned long)fixtureUserDataA == 20){
	    PhysicWorld::Instance()->getPlayer()->setSaltando(true);
	}

	//DETECTAR COGER(JUGADOR-CUBO)
	if((unsigned long) fixtureUserDataA== 100 && (unsigned long)fixtureUserDataB== 30){
	    std::cout<<"No puedes coger cubo"<<std::endl;
	    PhysicWorld::Instance()->getPlayer()->setPuedoCoger(false);
	}

	if((unsigned long)fixtureUserDataB == 100 && (unsigned long)fixtureUserDataA == 30){
	    std::cout<<"No puedes coger cubo"<<std::endl;
	    PhysicWorld::Instance()->getPlayer()->setPuedoCoger(false);
	}
}

MyContactListener::~MyContactListener(){}
