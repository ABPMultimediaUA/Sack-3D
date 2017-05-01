#include "../include/tluz.h"
#include <stdio.h>
#include <iostream>



char* Concat(char* base, char* anya);



TLuz::TLuz(float x, float y, float z, char* name, int tipe)
{
    intensidadA = glm::vec3(x*0.5,y*0.5,z*0.5);
    intensidadD = glm::vec3(x,y,z);
    nombreLuz= name;
    luzType= tipe;
    tipo= 3;
}

TLuz::~TLuz()
{
    //dtor
}

void TLuz::setPosicion(float x, float y,float z){

    posicion = glm::vec3(x,y,-z);

}


void TLuz::setIntensidad(glm::vec3 colr){
    intensidadA = glm::vec3(colr.x*0.5,colr.y*0.5,colr.z*0.5);
    intensidadD = glm::vec3(colr.x,colr.y,colr.z);;
}

glm::vec3 TLuz::getPos(){
    return posicion;
}

glm::vec3 TLuz::getIntensidad(){
    return intensidadD;
}

void TLuz::aplicarLuz(Shader* shad, glm::vec3 pos){
    setPosicion(pos.x,pos.y,pos.z);

    GLuint lightAmUniformLocation = glGetUniformLocation(shad->positionLocation(), Concat(nombreLuz,"Amb"));
    glUniform3fv(lightAmUniformLocation,1, &intensidadA[0]);

    GLuint lightUniformLocation = glGetUniformLocation(shad->positionLocation(), nombreLuz);
    glUniform3fv(lightUniformLocation,1, &intensidadD[0]);

    GLuint lightPosUniformLocation = glGetUniformLocation(shad->positionLocation(), Concat(nombreLuz,"Pos"));
    glUniform3fv(lightPosUniformLocation,1, &posicion[0]);
}


void TLuz::begingDraw(Shader* shad, std::vector<glm::mat4>* pila){
  /*  glm::vec3 posLuzAct;
    glm::mat4 matPosLuzAct;

    GLuint lightUniformLocation = glGetUniformLocation(shad->positionLocation(), nombreLuz);
    glUniform3fv(lightUniformLocation,1, &intensidad[0]);
    if(luzType == 1){ //Difusa

        GLuint lightPosUniformLocation = glGetUniformLocation(shad->positionLocation(), Concat(nombreLuz,"Pos"));

        matPosLuzAct = pila->at(pila->size()-1);

        posLuzAct = glm::vec3(matPosLuzAct * glm::vec4(glm::vec3(0,0,0), 1.0));
        //setPosicion(posLuzAct.x,posLuzAct.y,posLuzAct.z);
        glUniform3fv(lightPosUniformLocation,1, &posicion[0]);


*/



}
void TLuz::endDraw(std::vector<glm::mat4>* pila){
}
int TLuz::getTipo(){
    return tipo;
}
