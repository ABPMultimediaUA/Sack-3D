#include "ttransform.h"
#include <iostream>
extern std::vector<glm::mat4>* TEntidad::pila;

TTransform::TTransform()
{
      tipo=1;
      identidad();
    //ctor
}

TTransform::~TTransform()
{
    //dtor
}

void TTransform::identidad(){

    m_matriz= glm::mat4();
}
void TTransform::cargar(glm::mat4 Matriz){
    m_matriz= Matriz;
}
void TTransform::trasponer(){
    m_matriz = glm::transpose(m_matriz);
}

void TTransform::trasladar(glm::vec3 tras){
//    std::cout<<"HI"<<std::endl;
    glm::mat4 matrizTrans = glm::translate(tras);


     /*   for(int i =0; i<4;i++){
            for(int j =0; j<4;j++){
                std::cout<<matrizTrans[i][j];;
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;


        for(int i =0; i<4;i++){
            for(int j =0; j<4;j++){
                std::cout<<m_matriz[i][j];;
            }
            std::cout<<std::endl;
        }*/
    m_matriz = matrizTrans * m_matriz;

}
void TTransform::rotar(float grados, glm::vec3 eje){
    glm::mat4 matrizRot = glm::rotate(glm::radians(grados),eje);

      m_matriz = matrizRot * m_matriz;
}
void TTransform::escalar(glm::vec3 scala){
    glm::mat4 matrizScaled = glm::scale(scala);
    m_matriz = matrizScaled * m_matriz;
}

glm::mat4 TTransform::GetModel()const{
    return  m_matriz;
}

void TTransform::begingDraw(Shader* shad, glm::mat4 matCam){

    int tam=0;
    int pos;
   if(pila==0){
    pila = new std::vector<glm::mat4>;
    pila->push_back(matCam);
   }
    tam= pila->size();
    pos= tam-1;
    pila->push_back(( pila->at(pos) * this->GetModel()));
}

void TTransform::endDraw(){
    pila->pop_back();
    if(pila->size()==1){
        pila=0;
    }
}
int  TTransform::getTipo(){return tipo;}
