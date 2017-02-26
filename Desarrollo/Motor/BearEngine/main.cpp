#include <iostream>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "camera.h"
#include "display.h"
#include "tnodo.h"

#include "sceneloader.h"

//Malla
#include "mesh.h"


//Entidades
#include "tentidad.h"
#include "tentidadmalla.h"
#include "ttransform.h"

//Gestor

#include "tgestorrecursos.h"

#define WIDTH 800
#define HEIGHT 600


int main(int argc, char* argv[])
{
    std::cout << "Hello world!" << std::endl;
    Display display(WIDTH, HEIGHT, "Visor");
    TGestorRecursos gestor;
    //Shader shader("./res/basicShader");
    //Shader shader("./res/basicShaderLuz");
    Shader shader("./res/basicShaderToon");
    Camera cam(glm::vec3(0,0,-4), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f,1000.0f);
  //  Camera cam(glm::vec3(0,10,-100), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f,1000.0f);
    glm::mat4 camara = cam.GetViewProjection();
    TTransform* transformR= new TTransform;
  //  transformR->rotar(45,glm::vec3(0,1,0));
   // Mesh mesh("./res/Oso.obj");
    TTransform* transformTR= new TTransform;
    transformTR->trasladar(glm::vec3(0,0,0));
    std::cout << "Hello world!" << std::endl;
    TEntidadMalla* mallaUno = new TEntidadMalla();
   // mallaUno->setMalla( static_cast<Mesh*>(gestor.getRecurso("./res/Oso.obj",0)));
    TNodo raiz(1);
        raiz.setNombreEntidad("RAIZ");

    TNodo hijoUno(0);
        hijoUno.setNombreEntidad("Transf1Cam");
    TNodo hijoDos(0);
        hijoDos.setNombreEntidad("Transf2Cam");
    TNodo hijoTres(0);
        hijoTres.setNombreEntidad("Camara");
        hijoTres.setEntidad(&cam);
    TNodo hijoCuatro(0);
        hijoCuatro.setNombreEntidad("Transf1Malla");
        std::cout<<"Transformacion Rotacion "<<hijoCuatro.setEntidad(transformR)<<std::endl;;
    TNodo hijoCinco(0);
        hijoCinco.setNombreEntidad("Transf2Malla");
        std::cout<<"Transformacion Traslacion "<<hijoCinco.setEntidad(transformTR)<<std::endl;;

    TNodo hijoSeis(0);
        hijoSeis.setNombreEntidad("Malla");
       // std::cout<<"Malla "<<hijoSeis.setEntidad(mallaUno)<<std::endl;
        hijoSeis.setEntidad(mallaUno);
    raiz.addHijo(&hijoUno);
        raiz.addHijo(&hijoCuatro);

    hijoUno.addHijo(&hijoDos);
        hijoDos.addHijo(&hijoTres);

    hijoCuatro.addHijo(&hijoCinco);
        hijoCinco.addHijo(&hijoSeis);
    int malla;//Borrar y volver a cambiar update de display a void
    int actual =0; //Borrar y volver a cambiar update de display a void
    while(!display.IsClosed()){
        display.Clear(0.0f,0.15f,0.3f,1.0f);
        camara= cam.GetViewProjection();
        shader.Bind();
        //shader.Update(cam.GetViewProjection());
        raiz.draw(&shader, camara);

        malla=display.Update(cam);
/*Esto ira fuera*/
/**/        if(malla ==0){
/**/            if(actual!=0){
/**/                mallaUno->setMalla(0);
/**/                std::cout<<"SIN MALLA"<<std::endl;
/**/
/**/                actual=0;
/**/            }
/**/        }else if(malla==1){
/**/             if(actual!=1){
/**/               mallaUno->setMalla( static_cast<Mesh*>(gestor.getRecurso("./res/cubo.obj",0)));
/**/                //   std::cout<<"Malla "<<hijoSeis.setEntidad(mallaUno)<<std::endl;
/**/                actual=1;
/**/             }
/**/        }else if(malla==2){
/**/             if(actual!=2){
/**/                mallaUno->setMalla( static_cast<Mesh*>(gestor.getRecurso("./res/bear.obj",0)));
/**/                //std::cout<<"Malla "<<hijoSeis.setEntidad(mallaUno)<<std::endl;
/**/                actual=2;
/**/             }
/**/        }else if(malla==3){
/**/             if(actual!=3){
/**/                    mallaUno->setMalla( static_cast<Mesh*>(gestor.getRecurso("./res/andador.obj",0)));
                    // Para borrar un recurso concreto del vector */ gestor.borrarRecurso("./res/bear.obj");
/**/                //  std::cout<<"Malla "<<hijoSeis.setEntidad(mallaUno)<<std::endl;
/**/                actual=3;
/**/             }
/**/        }
/*Esto ira fuera*/
    }
    delete(transformR);
    delete(transformTR);
    delete(mallaUno);
    std::cout << "Bye world!" << std::endl;
    return 0;
}
