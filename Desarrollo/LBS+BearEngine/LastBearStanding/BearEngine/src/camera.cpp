#include "../include/camera.h"
#include <iostream>
Camera::Camera(){
	tipo=2;
    activada=0;
}


Camera::Camera( float fov, float aspect, float zNear, float zFar){
           m_perspective = glm::perspective(fov, aspect, zNear, zFar);
           esPerspectiva=1;
         //m_paralela = glm::ortho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);


            m_forward = glm::vec3(0,0,1);
            m_up = glm::vec3(0,1,0);
            tipo=2;
            activada=0;
}



void Camera::begingDraw(Shader* shad, std::vector<glm::mat4>* pila){

}
void Camera::endDraw(std::vector<glm::mat4>* pila){}

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
