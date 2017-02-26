#include "tentidadmalla.h"

TEntidadMalla::TEntidadMalla()
{
    mesh=0;
    tipo=1; //1 malla, 2 camara, 3 transformacion, 4
}

TEntidadMalla::~TEntidadMalla()
{
    //dtor
}

void TEntidadMalla::begingDraw(Shader* shad, glm::mat4 matCam){
   //Update Shader
 //   std::cout<<"DIBUJANDO..................."<<std::endl;

    int pos = pila->size()-1;
   //     std::cout<<pila<<std::endl;

    shad->Update(pila->at(pos),matCam);

  if(mesh)  mesh->Draw();
 /*  for(int i=0;i<meshes->size();i++){
        meshes->at(i)->Draw();
   }*/

}

void TEntidadMalla::endDraw(){
}

int  TEntidadMalla::getTipo(){
    return tipo;
}

void TEntidadMalla::setMalla(Mesh* azteca){
    mesh=azteca;
}/*
void TEntidadMalla::setMallas(std::vector<Mesh*>* aztecas){
    meshes=aztecas;
}*/
