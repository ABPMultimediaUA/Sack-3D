#include "camera.h"
#include <iostream>

void Camera::begingDraw(Shader* shad, glm::mat4 matCam){

}
void Camera::endDraw(){}

int Camera::getTipo(){
    return tipo;
}


void Camera::activarCamara(){
    activada=1;
}
void Camera::desactivarCamara(){
    activada=0;
}
int Camera::verActivadoCamara(){
    return activada;
}

glm::mat4 Camera::miraA(glm::vec3 pos, glm::vec3 direccion, glm::vec3 up){
    return glm::lookAt(pos,direccion,up);
}
