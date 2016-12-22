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
    /*
    //fuzzify distance and amount of ammo
    m_FuzzyModule.Fuzzify("DistanceToTarget", DistToTarget);
    m_FuzzyModule.Fuzzify("AmmoStatus", (double)m_iNumRoundsLeft);

    m_dLastDesirabilityScore = m_FuzzyModule.DeFuzzify("Desirability", FuzzyModule::max_av);
    */

    /*
    //Fuzzificar NJ-DJA-DJD-VJA-DA-VA-VAE-DAJD
    //DISTANCIA JUGADORES ARMADOS->DJA
    double DJA = getDistancia();
    m_FuzzyModule->Fuzzify("distancia", DJA);

    //DISTANCIA JUGADORES DESARMADOS->DJD
    double DJD = getDistancia();
    m_FuzzyModule->Fuzzify("distancia", DJD);

*/
    //DISTANCIA JUGADOR ARMADO
    double DJA;
    if(PhysicWorld::Instance()->getPlayer()->getCogiendo()){
        DJA = getDistancia(PhysicWorld::Instance()->getBot()->getBody(),
                           PhysicWorld::Instance()->getPlayer()->getBody());
    }
    else
        DJA = 0;
    m_FuzzyModule.Fuzzify("distancia", DJA);


    //DISTANCIA JUGADOR DESARMADO
    double DJD;
    if(PhysicWorld::Instance()->getPlayer()->getCogiendo()){
        DJD = 0;
    }
    else
        DJD = getDistancia(PhysicWorld::Instance()->getBot()->getBody(),
                           PhysicWorld::Instance()->getPlayer()->getBody());
    m_FuzzyModule.Fuzzify("distancia", DJD);


    //VALORACION ARMA JUGADOR ARMADO
    double VJA=0;
    if(PhysicWorld::Instance()->getPlayer()->getCogiendo()){
        VJA = PhysicWorld::Instance()->getPlayer()->getObjCogido()->getValoacion();
    }
    m_FuzzyModule.Fuzzify("valoracion", VJA);



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
    FzSet&& cerca = distancia.AddLeftShoulderSet("cerca",0, 25, 150);
    FzSet&& medio = distancia.AddTriangularSet("medio",25, 150, 300);
    FzSet&& lejos = distancia.AddRightShoulderSet("lejos",150, 300, 100000);

    //VALORACION
    FuzzyVariable& valoracion = m_FuzzyModule.CreateFLV("valoracion");
    FzSet mala = valoracion.AddLeftShoulderSet("mala",0,1,3);
    FzSet aceptable = valoracion.AddTriangularSet("aceptable",1,3,5);
    FzSet buena = valoracion.AddRightShoulderSet("buena",3,5,10);



    //PELIGRO
    FuzzyVariable& peligro = m_FuzzyModule.CreateFLV("peligro");
    FzSet mucho_p = peligro.AddLeftShoulderSet("poco_p",50,75,100);
    FzSet medio_p = peligro.AddTriangularSet("medio_p",25,50,75);
    FzSet poco_p  = peligro.AddRightShoulderSet("mucho_p",0,25,50);

    //AÑADIR REGLAS
    //VALORACION
    m_FuzzyModule.AddRule(buena, poco_p);
    m_FuzzyModule.AddRule(aceptable, medio_p);
    m_FuzzyModule.AddRule(mala, mucho_p);
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
    //mover();
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
   Destructor
*/
Bot::~Bot(){}
