#include "../include/tmaterial.h"
#include "../include/shader.h"
TMaterial::TMaterial(glm::vec3 colr, char* name)
{
    color = colr;
    nombre= name;
}

TMaterial::~TMaterial()
{
    //dtor
}

void TMaterial::Bind(){
    GLuint colorUniformLocation = glGetUniformLocation(1,"material");
    glUniform3fv(colorUniformLocation,1, &color[0]);
}

glm::vec3 TMaterial::getCol(){
    return color;
}

char* TMaterial::GetNombre(){
    return nombre;
}
void TMaterial::setNombre( char* name){
    nombre= name;
}
void TMaterial::setTipo(int tipo){
    type = tipo;
}
int TMaterial::GetTipo(){
    return type;
}
