#include "Bot.h"
#include "PhysicWorld.h"

using namespace std;



Bot::Bot(vector3df pos):Player(pos){
    IrrManager::Instance()->getManager()->getMeshManipulator()->setVertexColors(mesh->getMesh(), SColor(255,255,0,0));
    distancia = 0;
}

void Bot::update(){
    //mover();
    mesh->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    mesh->setRotation(vector3df(0,0,body->GetAngle()* 180 / 3.14159265));

    float x1 = PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().x;
    float x2 = PhysicWorld::Instance()->getBot()->getBody()->GetPosition().x;
    float y1 = PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().y;
    float y2 = PhysicWorld::Instance()->getBot()->getBody()->GetPosition().y;

    float x = pow( x2 - x1, 2);
    float y = pow( y2 - y1, 2);

    distancia = sqrt(x+y);

    //membresia
    //cerca 80 intermedio-140 lejos 200

    if (distancia<=80){
    	cerca = 255;
    	intermedio = 0;
    	lejos = 0;
    }
    if (distancia==140){
    	cerca = 0;
    	intermedio = 255;
    	lejos = 0;
    }
    if (distancia>=200){
    	cerca = 0;
    	intermedio = 0;
    	lejos = 255;
    }

    if(distancia<140 && distancia>80){
        //funciona
    	cerca = getMemership(distancia);
    	intermedio = 255-cerca;
    	lejos = 0;
    }
    if(distancia>140 && distancia<200){
    	lejos = getMemership(distancia);
    	intermedio = 255-lejos;
    	cerca = 0;
    }



    /*0- cerca 1-intermedio 2-lejos*/
    //std::cout<<"donde esta: "<<getMayorValor(cerca, intermedio, lejos)<<std::endl;

    switch(getMayorValor(cerca, intermedio, lejos)){
        case 0:
        	if(x2>x1){huir(1);}
        	else{huir(-1);}

        break;
        case 1: quieto();
        break;
        case 2: quieto();
        break;
        default: huir(1);
    }
}

int Bot::getMayorValor(int x1, int x2, int x3){
	if(x1>x2 && x1>x3){
		return 0;
	}
	else if(x2>x1 && x2>x3){
		return 1;
	}
	else
		return 2;
}

int Bot::getMemership(float d){
	int x;
	x = 255-(4.25*(d-80));
	return abs(x);
}
void Bot::huir(int dir){
	b2Vec2 velV = body->GetLinearVelocity();
    velV.x = vel*dir;
    body->SetLinearVelocity(velV);
}
void Bot::quieto(){

}
Bot::~Bot()
{
    //dtor
}
