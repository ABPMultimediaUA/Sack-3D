#include "../include/tentidadmalla.h"
#include "../include/texture.h"

TEntidadMalla::TEntidadMalla(Shader*shad)
{
    mesh=0;
    tipo=1; //1 malla, 2 camara, 3 transformacion, 4
    activo=0;
    texturaM=0;
    materialM =0;
    shadP=shad;
}

TEntidadMalla::~TEntidadMalla()
{
    //dtor
}

void TEntidadMalla::begingDraw(Shader* shad, std::vector<glm::mat4>* pila){
   if(shadP->positionLocation() == shad->positionLocation()){
   //Update Shader
 //   std::cout<<"DIBUJANDO..................."<<std::endl;

    int pos = pila->size()-1;
   //     std::cout<<pila<<std::endl;


    shad->Update(pila->at(pos));
    //shad->Update( pila->at(pos));
 if(texturaM){
      //  std::cout<<"Se aplica textura"<<std::endl;
        texturaM->Bind(0);}

  if(mesh)  mesh->Draw();
 /*  for(int i=0;i<meshes->size();i++){
        meshes->at(i)->Draw();
   }*/
   }

}

void TEntidadMalla::endDraw(std::vector<glm::mat4>* pila){
}

int  TEntidadMalla::getTipo(){
    return tipo;
}

void TEntidadMalla::asignarMat(TMaterial* mat){
    mesh->asignarMatM(mat);
    materialM = mat;
}


void TEntidadMalla::setMalla(Mesh* azteca){

    int found =0;
       //     std::cout<<"INICIO ARRAY DEL RECURSO"<<meshes.size()<<std::endl;

   // mesh=azteca;
   if(azteca){
    for(int i =0; i<meshes.size();i++){
        if(meshes.at(i)==azteca){
   //             std::cout<<"ESTA EN EL  ARRAY DEL RECURSO"<<std::endl;
            activo=i;
            found =1;
        break;
        }
    }
    if(!found){
  //      std::cout<<"NO ESTA EN EL  ARRAY DEL RECURSO"<<meshes.size()<<std::endl;
        meshes.push_back(azteca);
        activo = meshes.size()-1;
//    std::cout<<"INTRODUCIDO EN EL  ARRAY DEL RECURSO "<<meshes.size()<<std::endl;

    }

    activarMalla(activo);
   }else{
    mesh=0;
   }

//       meshes.push_back(azteca);
}/*
void TEntidadMalla::setMallas(std::vector<Mesh*>* aztecas){
    meshes=aztecas;
}*/

void TEntidadMalla::activarMalla(int i){
    mesh= meshes.at(i);
}

void TEntidadMalla::animar(){
   // std::cout<<activo<<",";
    activo++;
   // std::cout<<activo<<std::endl;
    if(activo>=meshes.size())
        activo=0;

     //     std::cout<<meshes.size()<<std::endl;

    activarMalla(activo);
}

void TEntidadMalla::resetAnimacion(){
    activarMalla(0);
}

void TEntidadMalla::verMallas(){
    for(int i=0; i<meshes.size();i++){
        std::cout<<meshes[i]->GetNombre()<<std::endl;
    }
}

void TEntidadMalla::verInformacionEMalla(){
    std::cout<<"Mallas en la entidad "<<meshes.size()<<std::endl;
    verMallas();
    std::cout<<"Malla activa "<<meshes[activo]->GetNombre()<<std::endl;
}

 void TEntidadMalla::setTextura(TRecurso* textura){
    texturaM = static_cast<Texture*> (textura);
 }

