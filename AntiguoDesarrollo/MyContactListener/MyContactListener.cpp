#include "MyContactListener.h"


//100->Cubs que se crean con el click
//20->Muelle 
MyContactListener::MyContactListener(){

}

void MyContactListener::BeginContact(b2Contact* contact){
	 void* fixtureUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
     void* fixtureUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();


	if((unsigned long)fixtureUserDataA == 100 && (unsigned long)fixtureUserDataB== 20){
	    std::cout<<"salta"<<std::endl;


	}

	if((unsigned long)fixtureUserDataB == 100 && (unsigned long)fixtureUserDataA == 20){
	    std::cout<<"salta"<<std::endl;
	}

}
void MyContactListener::EndContact(b2Contact* contact){
    void* fixtureUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* fixtureUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	if((unsigned long) fixtureUserDataA== 100 && (unsigned long)fixtureUserDataB== 20){
	    std::cout<<"No salta"<<std::endl;
	}

	if((unsigned long)fixtureUserDataB == 100 && (unsigned long)fixtureUserDataA == 20){
	    std::cout<<"No salta"<<std::endl;
	}
}

MyContactListener::~MyContactListener(){}
