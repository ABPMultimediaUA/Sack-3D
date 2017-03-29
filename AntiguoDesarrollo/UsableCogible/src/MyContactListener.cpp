#include "MyContactListener.h"
#include "PhysicWorld.h"

//100->Cubs que se crean con el click
//20->Muelle
MyContactListener::MyContactListener(){

}

void MyContactListener::BeginContact(b2Contact* contact){
	 void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
     void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

    //DETECTAR SALTO(JUGADOR-SUELO)
	if((unsigned long)fixtureUserDataA == 100 && (unsigned long)fixtureUserDataB== 20){
	    std::cout<<"Esta en el suelo"<<std::endl;
	     PhysicWorld::Instance()->getPlayer()->setSaltando(false);
	     PhysicWorld::Instance()->getPlayer()->setDobleSaltando(false);
	}

	if((unsigned long)fixtureUserDataB == 100 && (unsigned long)fixtureUserDataA == 20){
	    std::cout<<"Esta en el suelo"<<std::endl;
	     PhysicWorld::Instance()->getPlayer()->setSaltando(false);
	     PhysicWorld::Instance()->getPlayer()->setDobleSaltando(false);
	}

    //DETECTAR COGER(JUGADOR-CUBO)
	if((unsigned long)fixtureUserDataA == 100 && (unsigned long)fixtureUserDataB== 30){
	    std::cout<<"Puedes coger cubo"<<std::endl;
	    PhysicWorld::Instance()->getPlayer()->puedoCoger=true;
	}

	if((unsigned long)fixtureUserDataB == 100 && (unsigned long)fixtureUserDataA == 30){
	    std::cout<<"Puedes coger cubo"<<std::endl;
	    PhysicWorld::Instance()->getPlayer()->puedoCoger=true;
	}

}
void MyContactListener::EndContact(b2Contact* contact){
    void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
    void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

    //DETECTAR SALTO(JUGADOR-SUELO)
	if((unsigned long) fixtureUserDataA== 100 && (unsigned long)fixtureUserDataB== 20){
        PhysicWorld::Instance()->getPlayer()->setSaltando(true);
	    std::cout<<"Esta saltando"<<std::endl;
	}

	if((unsigned long)fixtureUserDataB == 100 && (unsigned long)fixtureUserDataA == 20){
        PhysicWorld::Instance()->getPlayer()->setSaltando(true);
	    std::cout<<"Esta saltando"<<std::endl;
	}

	//DETECTAR COGER(JUGADOR-CUBO)
	if((unsigned long) fixtureUserDataA== 100 && (unsigned long)fixtureUserDataB== 30){
	    std::cout<<"No puedes coger cubo"<<std::endl;
	    PhysicWorld::Instance()->getPlayer()->puedoCoger=false;
	}

	if((unsigned long)fixtureUserDataB == 100 && (unsigned long)fixtureUserDataA == 30){
	    std::cout<<"No puedes coger cubo"<<std::endl;
	    PhysicWorld::Instance()->getPlayer()->puedoCoger=false;
	}
}

MyContactListener::~MyContactListener(){}
