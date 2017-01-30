#include <iostream>


#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <stdlib.h>
#include <stdio.h>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "transform.h"
#include "camera.h"
#include "sceneloader.h"


#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define WIDTH 800
#define HEIGHT 600


int main(int argc, char* argv[]){

    Display display(WIDTH, HEIGHT, "Titulo");
  //  sceneLoader load("./res/bear.obj");
  //Triangulo
   /* Vertex vertices[]{ /*Triangulo*/
                     /*   Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0,0.0)   , glm::vec3(-1,-1,-1)),
                        Vertex(glm::vec3(0,0.5,0),     glm::vec2(0.5,-1.0)  , glm::vec3(-1,-1,-1)),
                        Vertex(glm::vec3(0.5,-0.5,0),  glm::vec2(1.0,0.0)   , glm::vec3(-1,-1,-1))

                      };



    unsigned int indices[]={0,1,2, 2,1,0};*/
  //CUBO
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

    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]),indices, sizeof(indices)/sizeof(indices[0]));
    Shader shader("./res/basicShader");
    Camera camera(glm::vec3(0,0,-4), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f,1000.0f);
    Transform transform;
    while(!display.IsClosed()){
        display.Clear(0.0f,0.15f,0.3f,1.0f);
        shader.Bind();
        shader.Update(transform, camera);
        mesh.Draw();
    //  load.draw();
        display.Update(camera);
    }
return 0;
}
