/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Bot.cpp

Author:        Estudio Rorschach
Created:
Modified:      08/12/2016 Jorge Puerto

Overview:

*******************************************************************************/
#include "Bot.h"
#include "PhysicWorld.h"


using namespace std;

#define RADTOGRAD 180 / 3.14159265  ///< Conversor de radianes a grados

/******************************************************************************
                               Bot
*******************************************************************************/


//---------------------------------------------------------------------------
/**
   Constructor
*/
Bot::Bot(vector3df pos):Player(pos){
    InicializarFuzzy();

}


double Bot::GetPeligro(){
    double DJA;
    double VJA=0;
    double DJD;
    double VA;

    //DISTANCIA JUGDOR ARMADO
    if(PhysicWorld::Instance()->getPlayer()->getCogiendo()){
        DJA = getDistancia(PhysicWorld::Instance()->getBot()->getBody(),
                           PhysicWorld::Instance()->getPlayer()->getBody());

        //Si esta armado añadimos la variable y calculamos la valoracion del arma para incluirla tambien
        if(DJA != 0){
            m_FuzzyModule.Fuzzify("distancia", DJA);

            //VALORACION ARMA JUGADOR ARMADO
            if(PhysicWorld::Instance()->getPlayer()->getCogiendo()){
                VJA = PhysicWorld::Instance()->getPlayer()->getObjCogido()->getValoracion();
            }
        }
    }

    //Si hay un jugador armado calculamos su valoracion
    if(VJA != 0) m_FuzzyModule.Fuzzify("valoracion", VJA);

    //DISTANCIA JUGADOR DESARMADO
    if(!PhysicWorld::Instance()->getPlayer()->getCogiendo()){
            DJD = getDistancia(PhysicWorld::Instance()->getBot()->getBody(),
                            PhysicWorld::Instance()->getPlayer()->getBody());

        m_FuzzyModule.Fuzzify("distancia", DJD*10);
        m_FuzzyModule.Fuzzify("valoracion", 0);
    }

    danger = m_FuzzyModule.DeFuzzify("peligro", FuzzyModule::centroid);
    return danger;
}

double Bot::getDistancia(b2Body* a, b2Body* b){
    double dis = 0;
    //float x1 = PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().x;
    double ax = a->GetPosition().x;
    double bx = b->GetPosition().x;
    double ay = a->GetPosition().y;
    double by = b->GetPosition().y;

    double x = pow( bx - ax, 2);
    double y = pow( by - ay, 2);

    dis = sqrt(x+y);

    return dis;
}
//---------------------------------------------------------------------------

void Bot::InicializarFuzzy(){

    //DISTANCIA

    FuzzyVariable& distancia = m_FuzzyModule.CreateFLV("distancia");
    FzSet cerca = distancia.AddLeftShoulderSet("cerca",0, 25, 150);
    FzSet medio = distancia.AddTriangularSet("medio",25, 150, 300);
    FzSet lejos = distancia.AddRightShoulderSet("lejos",150, 300, 100000);

    //VALORACION DEL ARMA DEL ENEMIGO
    FuzzyVariable& valoracion = m_FuzzyModule.CreateFLV("valoracion");
    FzSet mala = valoracion.AddLeftShoulderSet("mala",0,10,30);
    FzSet aceptable = valoracion.AddTriangularSet("aceptable",10,30,50);
    FzSet buena = valoracion.AddRightShoulderSet("buena",30,50,100);

    //PELIGRO
    FuzzyVariable& peligro = m_FuzzyModule.CreateFLV("peligro");
    FzSet mucho_p = peligro.AddLeftShoulderSet("mucho_p",50,75,100);
    FzSet medio_p = peligro.AddTriangularSet("medio_p",25,50,75);
    FzSet poco_p  = peligro.AddRightShoulderSet("poco_p",0,25,50);

    //AÑADIR REGLAS

    //VALORACION
    m_FuzzyModule.AddRule(buena, mucho_p);
    m_FuzzyModule.AddRule(aceptable, medio_p);
    m_FuzzyModule.AddRule(mala, poco_p);

    //DISTANCIA
    m_FuzzyModule.AddRule(lejos, poco_p);
    m_FuzzyModule.AddRule(medio, medio_p);
    m_FuzzyModule.AddRule(cerca, mucho_p);

    //VALORACIOM Y DISTANCIA

    //

}

/**
   Actualizar
*/
void Bot::update(){
    if(puedoCoger && !cogiendo){
        this->crearJoint();
        this->setObjCogido(this->getObjPuedoCoger());
    }
    mover();
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()*RADTOGRAD));

    std::cout<<"Pel: "<<GetPeligro()<<std::endl;
}

//---------------------------------------------------------------------------
/**

*/
void Bot::quieto(){

}
//---------------------------------------------------------------------------
/**

*/
void Bot::mover(){

    double peligro = GetPeligro();

    if(this->getCogiendo()){
        //si esta armado y el peligro es bajo debera buscar un recorrido hacia un jugador
        //si el peligro es muy alto debera huir
        if(peligro<50){
            //Vamos a suponer que busca el camino correcto hacia un jugador y decide que tiene que ir a por el
            //En este caso solo seguiremos al jugador en x
            seguirCamino(2);
        }else{
            //Si el peligro es muy alto buscara un camino por el que huir
            //Ahora solamente corre en direccion contraria
            seguirCamino(1);
        }
    }else{
        //si NO esta armado y el peligro es bajo debera buscar un recorrido hacia un arma
        //si el peligro es muy alto debera huir
        if(peligro<=50){
            //Vamos a suponer que busca el camino correcto y decide que el arma que debe coger
            //es la que tiene en la misma plataforma a su derecha
            body->SetLinearVelocity(b2Vec2 (1*vel, body->GetLinearVelocity().y));
        }else{
            //Si el peligro es muy alto buscara un camino por el que huir
            //Ahora solamente corre en direccionc contraria
            seguirCamino(1);
        }
    }

}

void Bot::seguirCamino(int i){

    float x1 = PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().x;
    float x2 = PhysicWorld::Instance()->getBot()->getBody()->GetPosition().x;
    int dir;

    if(i == 1){if(x2>x1) dir=1; else dir=-1;}
    else{if(x2>x1) dir=-1; else dir=1;}

	b2Vec2 velV = body->GetLinearVelocity();
    velV.x = vel*dir;
    body->SetLinearVelocity(velV);
}

//---------------------------------------------------------------------------
/**
   Destructor
*/
Bot::~Bot(){}
