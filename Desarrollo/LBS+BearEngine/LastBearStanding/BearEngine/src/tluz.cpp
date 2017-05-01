#include "../include/tluz.h"
#include <stdio.h>
#include <iostream>
TLuz::TLuz(float x, float y, float z, char* name)
{
    intensidad = glm::vec3(x,y,z);
    nombreLuz= name;
}

TLuz::~TLuz()
{
    //dtor
}

void TLuz::setPosicion(float x, float y,float z){

    posicion = glm::vec3(x,y,z);

}


void TLuz::setIntensidad(glm::vec3 colr){
    intensidad = colr;
}

glm::vec3 TLuz::getIntensidad(){
    return intensidad;
}

void TLuz::begingDraw(Shader* shad, std::vector<glm::mat4>* pila){

    GLuint lightUniformLocation = glGetUniformLocation(shad->positionLocation(), nombreLuz);
    glUniform3fv(lightUniformLocation,1, &intensidad[0]);

}
void TLuz::endDraw(std::vector<glm::mat4>* pila){
}
int TLuz::getTipo(){
    return tipo;
}
