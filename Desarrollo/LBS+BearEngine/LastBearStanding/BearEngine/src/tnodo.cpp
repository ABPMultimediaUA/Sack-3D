#include "../include/tnodo.h"

TNodo::TNodo(int cepa )// cepa 1 es raiz, 0 no es raiz
{
    raiz=cepa;
    entidad=0;

}

TNodo::~TNodo()
{
    //dtor
    std::cout<<"Borrado "<<this->getNombreEntidad()<<std::endl;
    for(int i=0; i<hijos.size();i++){
        delete(hijos.at(i));
    }

}


int TNodo::addHijo(TNodo* hijo){
    hijos.push_back(hijo);
    hijo->setPadre(this);
    return (hijos.size()-1);
}

int TNodo::remHijo(TNodo* hijo){
    int borrado=0;
    for(int i=0; i<hijos.size();i++){
        if(hijos[i]==hijo){
             hijos.erase(hijos.begin()+i);
             hijo->setPadre(NULL);
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

void TNodo::verArbol(){
   if(esRaiz()){
       std::cout<<"ARBOL DE ESCENA"<<std::endl;
       std::cout<<std::endl;
    }
    std::cout<<getNombreEntidad();
    std::cout<<" Tiene "<<hijos.size()<<" hijos";
    if(esRaiz()){
                std::cout<<std::endl;
    }
    if(getPadre()){
        std::cout<<"|PADRE "<<getPadre()->getNombreEntidad()<<" |";
    }
    std::cout<<std::endl;
    for(int i =0; i<hijos.size(); i++){
        hijos[i]->verArbol();
    }
    if(!hijos.size()){
        std::cout<<std::endl;
    }

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

    if(visible){
            entidad->begingDraw(shad,  pila);
        }

    }

    for(int i=0; i<hijos.size();i++){
        hijos.at(i)->draw(shad, pila);
    }

    if(entidad){
        if(visible){
            entidad->endDraw(pila);
        }
    }

}

  void TNodo::setVisible(int visi){
    visible=visi;
  }
  int TNodo::getVisible(){
    return visible;
  }
