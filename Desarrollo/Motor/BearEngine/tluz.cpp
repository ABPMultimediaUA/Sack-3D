#include "tluz.h"

TLuz::TLuz()
{
    intensidad = glm::vec3(1,1,1);
}

TLuz::~TLuz()
{
    //dtor
}

void TLuz::setIntensidad(glm::vec3 colr){
    intensidad = colr;
}

glm::vec3 TLuz::getIntensidad(){
    return intensidad;
}

void TLuz::begingDraw(Shader* shad, glm::mat4 mat){
}
void TLuz::endDraw(){
}
int TLuz::getTipo(){
    return tipo;
}
