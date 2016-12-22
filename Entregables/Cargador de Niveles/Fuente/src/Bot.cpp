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

#define CERCA 20
#define MEDIA CERCA*2
#define LEJOS CERCA*3
#define RADTOGRAD 180 / 3.14159265  ///< Conversor de radianes a grados

/******************************************************************************
                               Bot
*******************************************************************************/


//---------------------------------------------------------------------------
/**
   Constructor
*/
Bot::Bot(vector3df pos):Player(pos){
    //IrrManager::Instance()->getManager()->getMeshManipulator()->setVertexColors(mesh->getMesh(), SColor(255,255,0,0));
    distancia = 0;
}
//---------------------------------------------------------------------------
/**
   Actualizar
*/
void Bot::update(){
    //mover();
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()*RADTOGRAD));

    int accion = calcularPeligro();


}
//---------------------------------------------------------------------------
/**

*/
int Bot::getMemership(float d){
	int x;
	x = (4.25*(d-80));
	return x;
}
//---------------------------------------------------------------------------
/**

*/
void Bot::calcularAccion(float peligro){ //grafica fuzzy logic de peligro <20 Poco, 20-190 Medio, >190 Mucho
    
    float ppoco  = 0.0f;
    float pmedio = 0.0f;
    float pmucho = 0.0f;
    //varibale random para determinar ataque sorpresa
    //hacemos un random entre 0 y 100 (101 valores) y 
    //dividimos por 100 para que sea entre 0 y 1.
    float random = ((double) rand() / (RAND_MAX));
    random = roundf(random * 100) / 100;

    //std::cout<<"Random= "<<random<<std::endl;


//////***PELIGRO MUCHO***//////////

    if(peligro<=20) huir();
    
//////***PELIGRO POCO***//////////

    else if(peligro>= 190){      
        /*if(getObjCogido()!=0){ //con arma
            atacar(); //
        }
        else if(getObjCogido() == 0){ //sin arma
            buscarArma();
        }*/
    }


//////***PELIGRO MEDIO***//////////

    else if(peligro>20 && peligro<190){
        
        if(peligro<=105){  //peligro MUCHO-MEDIO
            ppoco = 0;
            pmedio = (1.0f/85.0f)*peligro -(4.0f/17.0f);
            pmucho = 1.0f -pmedio;

            /*if(getObjCogido()!= 0){ //CON ARMA

                if(random <= getMayorPeligro(pmedio, pmucho)){   //accion normal
                    huir();
                }
                else{                                            //accion sopresa
                    buscarJugadorCerca();
                }
            }
            else{                // SIN ARMA
                buscarArma();
            }*/
                 
        }
        else if(peligro>105){  //peligro MEDIO-POCO
            pmucho = 0;
            ppoco = (1.0f/85.0f)*peligro -(21.0f/17.0f);
            pmedio = 1.0f-ppoco;

            /*if(getObjCogido()!= 0){ //CON ARMA

                buscarJugadorCerca;
            }
            else{                // SIN ARMA
             
                if(random <= getMayorPeligro(ppoco, pmedio)){   //accion normal
                    huir();
                }
                else{                                           //ataque sopresa
                    buscarJugadorCerca();
                }
            }*/
            
        }
        /*std::cout<<"PELIGRO"<<std::endl;
        std::cout<<"Poco: "<<ppoco<<std::endl;
        std::cout<<"Medio: "<<pmedio<<std::endl;
        std::cout<<"Mucho: "<<pmucho<<std::endl;
        std::cout<<" "<<std::endl;*/
    }

}
//---------------------------------------------------------------------------
/**

*/
float Bot::calcularPeligro(){

    //variables que calculan peligro:
	int VAE = 0; //valoracion arma equipada
	int DJA = 0; //distancia jugadores armados mas cercano
	int VJA = 0; //valoracion armas jugadores armados el mas cercano
	int DAJD= 0; //distancia a arma jugadores desarmados el mas cercano
	int DA  = 0; //distancia arma alcance
	int VA  = 0; //valoracion arma alcance
	int NJ  = 0; //numero jugadores
	int DJD = 0; //distancia jugador desarmado mas cercano

    //float distancia = valorarDistancia(body, body); //OK

    //VAE  = getObjCogido().getValoracion(); //implememntado en el proyecto de miguel Pani
    //DJA  = valorarDistancia( PhysicWorld::Instance()->getBot()->getBody(), getJugadorCerca() ); 
    //VJA  = getJugadorCerca().getObjCogido().getValoracion(); 
    //DAJD = valorarDistancia( getJugadorCerca(), getArmaCercana() );
    //DA   = valorarDistancia( this.getBody(), getArmaCercana() );
    //VA   = getArmaCercana().getValoracion();
    //NJ   = getNumJugadores(); //falta metodo de obtener jugadores.
    //DJD  = valorarDistancia( this.getBody(), getJugadorCercanoDes());

    int totalPeligro = VAE+DJA+VJA+DAJD+DA+VA+NJ+DJD; //esto es el peligro que tiene en cada momento
    
    calcularAccion(189); //le pasamos numero cualquiera para calcular la accion


    //float distancia = valorarDistancia(PhysicWorld::Instance()->getPlayer()->getBody(), 
     //                                PhysicWorld::Instance()->getBot()->getBody()     );

    //std::cout<<"distancia: "<<distancia<<std::endl;
    return 0;

}
//---------------------------------------------------------------------------
/**

*/
float Bot::valorarDistancia(b2Body* a, b2Body* b){

    //float x1 = PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().x;
    float ax = a->GetPosition().x;
    float bx = b->GetPosition().x;
    float ay = a->GetPosition().y;
    float by = b->GetPosition().y;

    float x = pow( bx - ax, 2);
    float y = pow( by - ay, 2);

    distancia = sqrt(x+y);
    //std::cout<<"distancia: "<<distancia<<std::endl;

    //membresia

    if (distancia<=CERCA){ //umbral de solo cerca
    	cerca = 1;
        intermedio = 0;
        lejos = 0;
    }
    if (distancia==MEDIA){  //linea central
    	cerca = 0;
        intermedio = 1;
        lejos = 0;
    }
    if (distancia>=LEJOS){  //umbral solo lejos
    	cerca = 0;
        intermedio = 0;
        lejos = 1;
    }

    if(distancia<MEDIA && distancia>CERCA){ //caso cerca y medio
    	intermedio = (0.05*distancia) - 1;
    	cerca = 1 - intermedio;
    	lejos = 0;

    }
    if(distancia>MEDIA && distancia<LEJOS){ //caso medio y lejos
    	lejos = (0.025*distancia) -1;
    	intermedio = 1 - lejos;
    	cerca = 0;
    }

    std::cout<<"cerca: "<<cerca<<std::endl;
    std::cout<<"intermedio: "<<intermedio<<std::endl;
    std::cout<<"lejos: "<<lejos<<std::endl;
    //conseguimos el mayor de ellos y buscamos si es 0, 1 o 2:

    distancia = getMayorValor(cerca, intermedio, lejos);

    return distancia;
}
//---------------------------------------------------------------------------
/**

*/
int Bot::getMayorValor(float x1, float x2, float x3){
    if(x1>x2 && x1>x3){
        return 0;
    }
    else if(x2>x1 && x2>x3){
        return 1;
    }
    else
        return 2;
}
//---------------------------------------------------------------------------
/**

*/
float Bot::getMayorPeligro(float x1, float x2){
    if(x1>x2){
        return x1;
    }
    else
        return x2;
}
//---------------------------------------------------------------------------
/**

*/
int Bot::getNumJugadores(){
    int numero = 0;
    //numero = PhysicWorld::Instance()->getJugadores();
    if(numero == 3)     return 1;
    else if(numero ==2) return 2;
    else                return 3;  
}
//---------------------------------------------------------------------------
/**

*/
void Bot::huir(){
	
}
//---------------------------------------------------------------------------
/**

*/
void Bot::buscarArma(){

}
//---------------------------------------------------------------------------
/**

*/
void Bot::getJugadorCerca(){

}
//---------------------------------------------------------------------------
/**

*/
void Bot::buscarJugadorCerca(){

}
//---------------------------------------------------------------------------
/**

*/
void Bot::atacar(){

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
