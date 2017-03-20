#include "tnodo.h"

TNodo::TNodo(int cepa )// cepa 1 es raiz, 0 no es raiz
{
    raiz=cepa;
    entidad=0;
}

TNodo::~TNodo()
{
    //dtor
    for(int i=0; i<hijos.size();i++){
        delete(hijos.at(i));
    }
    std::cout<<"Borrado Arbol"<<std::endl;
}


int TNodo::addHijo(TNodo* hijo){
    hijos.push_back(hijo);
    return (hijos.size()-1);
}

int TNodo::remHijo(TNodo* hijo){
    int borrado=0;
    for(int i=0; i<hijos.size();i++){
        if(hijos[i]==hijo){
             hijos.erase(hijos.begin()+i);
             borrado=1;
        }
    }
    return borrado;
}
bool TNodo::setEntidad(TEntidad *entity){
    return  entidad=entity;
}

void TNodo::setNombreEntidad(char* name){
    nombreEntidad=name;
}
char* TNodo::getNombreEntidad(){

    return nombreEntidad;

}

TEntidad* TNodo::getEntidad(){
    return entidad;
}
TNodo* TNodo::getPadre(){
    return padre;
}
void TNodo::setPadre(TNodo* butanero){
    padre= butanero;
}
int TNodo::esRaiz(){
    return raiz;
}

void TNodo::draw(Shader* shad, std::vector<glm::mat4>* pila){

   // std::cout<<"Dibujando "<<nombreEntidad<<std::endl;
   if(entidad){
     //   std::cout<<"Hay entidad "<<nombreEntidad<<std::endl;

        entidad->begingDraw(shad, pila);


    }

    for(int i=0; i<hijos.size();i++){
        hijos.at(i)->draw(shad, pila);
    }

    if(entidad){
        entidad->endDraw(pila);

    }

}
