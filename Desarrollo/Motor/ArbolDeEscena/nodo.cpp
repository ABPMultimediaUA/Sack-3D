#include "nodo.h"
#include <iostream>
Nodo::Nodo(int raiz)
{

esRaiz=raiz;
tienePadre=0;

}

Nodo::~Nodo()
{
    //dtor
}

int Nodo::addHijo(Nodo* hijo){ //1 se ha anaydido bien 0 no

if(hijo!=nullptr){
    hijo->setPadre(this);
    hijos.push_back(hijo);
    return 1;
}

return 0;
}

int Nodo::remHijo(Nodo* hijo){ //1 se ha borrado bien 0 no
    /*< A LO CUTRE>*/
    int borrado=0;

    for(int i =0; i<hijos.size();i++){
        if(hijo!=nullptr){
            if(hijos[i]==hijo){
                hijos.erase(hijos.begin()+i);
                borrado=1;
            }
        }
    }

    /*</A LO CUTRE>*/

    return borrado;
}
int Nodo::conPadre(){
    return tienePadre;
}
Nodo* Nodo::getPadre(){
    return padre;
}
void Nodo::setPadre(Nodo* padreN){
    tienePadre=1;
    padre   =   padreN;
}

int Nodo::numeroHijos(){
    return hijos.size();
}

void Nodo::draw(Shader* shad, Camera* cam, Transform* trans){

    if( !esRaiz){

        entidad->begingDraw();

        if(entidad->getTipo()==0){
           std::cout<<"Tipo Malla"<<std::endl;
        }
        else if(entidad->getTipo()==1){
            std::cout<<"Tipo Transformacion"<<std::endl;
        }else if(entidad->getTipo()==2){
            std::cout<<"Tipo Camara"<<std::endl;
            cam= (Camera*) entidad;
        }else if(entidad->getTipo()==3){
            std::cout<<"Tipo Luz"<<std::endl;
        }
    shad->Update(trans, cam);
    }else{
        std::cout<<"La RAIZ"<<std::endl;
    }


    for(int i=0;i<hijos.size();i++){

        hijos[i]->draw(shad, cam, trans);
        std::cout<<"Siguiente hijo"<<std::endl;

    }

    if( !esRaiz){
        entidad->endDraw();
    }
}

bool Nodo::seTEntidad(TEntidad* entidadN){
    entidad = entidadN;
}
void Nodo::setRaiz(int siONo){
    esRaiz= siONo;
}
