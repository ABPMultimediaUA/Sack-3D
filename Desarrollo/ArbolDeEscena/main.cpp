#include <iostream>


#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <stdlib.h>
#include <stdio.h>

#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "nodo.h"

#include"transform.h"
#include"camera.h"



#define WIDTH 800
#define HEIGHT 600
using namespace std;

int main(int argc, char* argv[]){
    Display display(WIDTH, HEIGHT, "Titulo");
    Shader shader("./res/basicShader");
   // Camera camera(glm::vec3(0,0,-4), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f,1000.0f);
   Camera camera;
    Transform transform;
    Nodo raiz(1);
    Nodo hijoUno(0); // Nodo Camara
    Nodo hijoDos(0) ; //Nodo Malla

    std::cout<< "Hay  "<< raiz.numeroHijos()<<" hijos" <<std::endl; //0 hijos
    std::cout<< "Anyadimos hijo Uno -> "<<raiz.addHijo(&hijoUno)<<std::endl; //1 exito 0 fallo
    std::cout<< "Anyadimos hijo Dos a raiz-> "<<raiz.addHijo(&hijoDos)<<std::endl; //1 exito 0 fallo
    std::cout<< "En la raiz hay  "<< raiz.numeroHijos()<<" hijos" <<std::endl; //1 hijos
    std::cout<< "En la raiz hay  "<< raiz.numeroHijos()<<" hijos" <<std::endl; //1 hijos
  //  std::cout<< "Borramos hijo Uno -> "<<raiz.remHijo(&hijoUno)<<std::endl; //1 exito 0 fallo
   // std::cout<< "Hay  "<< raiz.numeroHijos()<<" hijos" <<std::endl; // 1 hijo

      Vertex vertices[]{   Vertex(glm::vec3(-0.5    ,   -0.5   ,   -0.5), glm::vec2(1.0,1.0), glm::vec3(-1,-1,-1)), //0 abajo  Derecha
                         Vertex(glm::vec3(-0.5  ,   0.5     ,   -0.5), glm::vec2(1.0,0.0), glm::vec3(-1,1,-1)), //1 arriba Derecha
                         Vertex(glm::vec3(0.5   ,   0.5     ,   -0.5), glm::vec2(0.0,0.0), glm::vec3(1,1,-1)),  //2 arriba izquierda
                         Vertex(glm::vec3(0.5   ,   -0.5    ,   -0.5), glm::vec2(0.0,1.0), glm::vec3(1,-1,-1)),  //3 abajo izquierda

                         Vertex(glm::vec3(-0.5    ,   -0.5   ,   0.5), glm::vec2(0.0,1.0), glm::vec3(-1,-1,1)), //4 abajo  Derecha
                         Vertex(glm::vec3(-0.5  ,   0.5     ,   0.5), glm::vec2(0.0,0.0), glm::vec3(-1,1,1)), //5 arriba Derecha
                         Vertex(glm::vec3(0.5   ,   0.5     ,   0.5), glm::vec2(1.0,0.0), glm::vec3(1,1,1)),  //6 arriba izquierda
                         Vertex(glm::vec3(0.5   ,   -0.5    ,   0.5), glm::vec2(1.0,1.0), glm::vec3(1,-1,1)),  //7 abajo izquierda
/*LAS NORMALES DEL CUBO ESTAN MAL PUESTAS*/
    };

       unsigned int indices[] =
            {
                0,1,3,      1,2,3,  //Cara frontal
                5,1,0,      0,4,5,  //Cara derecha
                2,6,7,      7,3,2,  //Cara Izquierda
                7,5,4,      5,7,6,  //Cara Trasera
                1,5,6,      1,6,2,  //Cara Superior
                0,7,4,      0,3,7   //Cara Inferior
            };

//Persona *Pepito = new Estudiante("Jose");


TEntidad* entidi = new Mesh(vertices, sizeof(vertices)/sizeof(vertices[0]),indices, sizeof(indices)/sizeof(indices[0]));
TEntidad* cam = new Camera(glm::vec3(0,0,-4), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f,1000.0f);
;
//Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]),indices, sizeof(indices)/sizeof(indices[0]));
//Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]),indices, sizeof(indices)/sizeof(indices[0]));
Transform transforma(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,1.0f,1.0f));
hijoDos.seTEntidad(entidi);
hijoUno.seTEntidad(cam);
glm::mat4 modeloBase = transforma.GetModel();
glm::vec3 vectres;


for(int i =0; i<4;i++){
    for(int j =0; j<4;j++){
        std::cout<<modeloBase[i][j]<<",";
    }
    std::cout<<std::endl;
}

     while(!display.IsClosed()){
        display.Clear(0.0f,0.15f,0.3f,1.0f);
        shader.Bind();


      //  shader.Update(transform, camera);
        raiz.draw(&shader, &camera,&transform);
       // mesh.Draw();
        display.Update();
    }
    return 0;
}
