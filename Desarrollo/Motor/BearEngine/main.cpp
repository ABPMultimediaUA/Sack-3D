#include <iostream>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <glm/glm.hpp>

#include "shader.h"

#include "display.h"
#include "tnodo.h"

//#include "sceneloader.h"



//Entidades
#include "tentidad.h"
//#include "tentidadmalla.h"
//#include "ttransform.h"
//#include "camera.h"

//Recursos
//#include "mesh.h"
//#include "tluz.h"

//Gestor

#include "tgestorrecursos.h"

#include "tmotorbear.h"

#define WIDTH 1080
#define HEIGHT 720
/*
#define WIDTH 1920
#define HEIGHT 1280
*/

int main(int argc, char* argv[])
{
    std::cout << "Hello world!" << std::endl;
    TMotorBear motorsito(WIDTH, HEIGHT, "Bear Engine");
    //Shader shader("./res/basicShader");
    //Shader shader("./res/basicShaderLuz");
    Shader shader("./res/basicShaderToon");

 /*   TLuz luz;
    luz.setIntensidad(glm::vec3(0,0,0));

    glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(luz.getIntensidad()));
    glEnable(GL_LIGHT0);
*/

    /*Funciones de la fachada*/

    TEntidad *transf1 = motorsito.crearTransform();
  //  transf1->rotar(45,glm::vec3(0,1,0));
    TEntidad *transf2 = motorsito.crearTransform();
    //transf2->trasladar(glm::vec3(-1,0,0));

    TEntidad *transf3 = motorsito.crearTransform();

    TEntidad *transf4 = motorsito.crearTransform();
//    motorsito.transformarEntidad(transf4,0,glm::vec3(-1,0,0));

  //  transf4->trasladar(glm::vec3(0,2,0));

    TEntidad *transf5 = motorsito.crearTransform();
    TEntidad *transf6 = motorsito.crearTransform();
   // motorsito.transformarEntidad(transf6,0,glm::vec3(1,-4,0));

//    transf6->trasladar(glm::vec3(1,-4,0));

    TEntidad *transf7 = motorsito.crearTransform();
    TEntidad *transf8 = motorsito.crearTransform();
        motorsito.transformarEntidad(transf8,0,glm::vec3(1,2,0));

//    transf8->trasladar(glm::vec3(1,2,0));

    TEntidad *transf9 = motorsito.crearTransform();
    TEntidad *transf10 = motorsito.crearTransform();

    motorsito.transformarEntidad(transf10,0,glm::vec3(-1,-2,0));

//    transf10->trasladar(glm::vec3(-1,-2,0));

    TEntidad *transf11 = motorsito.crearTransform();
    TEntidad *transf12 = motorsito.crearTransform();
    //    motorsito.transformarEntidad(transf11,45,glm::vec3(0,1,0));

    motorsito.transformarEntidad(transf12,0,glm::vec3(-1,2,0));
//    transf12->trasladar(glm::vec3(-1,2,0));

    TEntidad *transf13 = motorsito.crearTransform();
    TEntidad *transf14 = motorsito.crearTransform();

    //   motorsito.transformarEntidad(transf13,45,glm::vec3(0,0,1));

    TEntidad *transf15 = motorsito.crearTransform();
    TEntidad *transf16 = motorsito.crearTransform();
    TEntidad *transfEsc = motorsito.crearTransform();

//    motorsito.transformarEntidad(transf14,0,glm::vec3(1,0,0));

//    transf14->trasladar(glm::vec3(1,0,0));


   // transf4->trasladar(glm::vec3(-0.5,0,0));

    //TEntidad * malla1  =new TEntidadMalla();// motorsito.crearMalla("./res/cubo.obj");
    TEntidad * malla1  =motorsito.crearMalla("./res/andador1.obj");
    motorsito.cambiarMalla(malla1,"./res/andador2.obj");
    motorsito.cambiarMalla(malla1,"./res/andador3.obj");
    motorsito.cambiarMalla(malla1,"./res/andador4.obj");
    motorsito.cambiarMalla(malla1,"./res/andador5.obj");
    motorsito.cambiarMalla(malla1,"./res/andador6.obj");


    TEntidad * malla2  =motorsito.crearMalla("./res/cubo.obj");
  //  TEntidad * malla2  =motorsito.crearMalla("./res/cubo.obj");
    //TEntidad * malla3  =motorsito.crearMalla("./res/bear.obj");
 //   TEntidad * malla4  =motorsito.crearMalla("./res/andador.obj");
//    TEntidad * malla4  =new TEntidadMalla();
    //TEntidad * malla4  =motorsito.crearMalla(3,3, 0.05);
    //TEntidad * malla5  =motorsito.crearMalla("./res/cubo.obj");
    //TEntidad * malla6  =motorsito.crearMalla("./res/cubo.obj");

   /* motorsito.crearCuboEn(0.05,0.05,0.05,glm::vec3(0,0,-0.05));
    motorsito.crearCuboEn(0.05,0.05,0.05,glm::vec3(0,0.06,-0.05));
    motorsito.crearCuboEn(0.05,0.005,0.005,glm::vec3(0,-0.06,-0.05));
    motorsito.crearCuboEn(0.05,0.05,0.05,glm::vec3(0,-0.12,-0.05));*/

    TEntidad * cam = motorsito.crearCamara(glm::vec3(0,0,-4), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f,1000.0f);


    TEntidad * camDos = motorsito.crearCamara(glm::vec3(0,0,-4), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f,1000.0f);

    TNodo* nodoTrans1 = motorsito.crearNodo(motorsito.getRaiz(),transf1, "Trans1");
    TNodo* nodoTrans2 = motorsito.crearNodo(nodoTrans1,transf2, "Trans2");
    TNodo* nodoMalla1 = motorsito.crearNodo(nodoTrans2,malla1,"malla1");
    TNodo* nodoTrans15 = motorsito.crearNodo(motorsito.getRaiz(),transf15, "Trans15");
    TNodo* nodoTrans16 = motorsito.crearNodo(nodoTrans15,transf16, "Trans16");
    TNodo* nodoCamara1 = motorsito.crearNodo(nodoTrans16,cam,"Cam1");
   // motorsito.transformarEntidad(transf16,0,glm::vec3(0,65,100));

    TNodo* nodoTrans3 = motorsito.crearNodo(motorsito.getRaiz(),transf3,"Trans3");
    TNodo* nodoTrans4 = motorsito.crearNodo(nodoTrans3,transf4,"Trans4");
    TNodo* nodoCamara2 = motorsito.crearNodo(nodoTrans4,camDos, "cam2");


/**PRUEBAS PARA HUD CON CAMARA**/ //HUD NECESITA UN SHADER PROPIO QUE NO LE AFECTE LA LUZ Y APLIQUE TEXTURA
    //TNodo* nodoTrans5 = motorsito.crearNodo(motorsito.getRaiz(),transf5, "Trans5");
    TNodo* nodoTrans5 = motorsito.crearNodo(nodoTrans16,transf5, "Trans5");
    TNodo* nodoTransEsc = motorsito.crearNodo(nodoTrans5,transfEsc, "TransEscala");
    TNodo* nodoTrans6 = motorsito.crearNodo(nodoTransEsc,transf6, "Trans6");
    TNodo* nodoMalla2 = motorsito.crearNodo(nodoTrans6,malla2,"malla2");
    motorsito.transformarEntidad(transf6,0,glm::vec3(0,-1.25,-1500));
    motorsito.escalarEntidad(transfEsc,glm::vec3(1,0.5,0.001));
    motorsito.transformarEntidad(transf16,0,glm::vec3(0,1.5,5));


/**FIN PRUEBAS PARA HUD CON CAMARA**/

    TNodo* nodoTrans7 = motorsito.crearNodo(motorsito.getRaiz(),transf7, "Trans7");
    TNodo* nodoTrans8 = motorsito.crearNodo(nodoTrans7,transf8, "Trans8");
  //  TNodo* nodoMalla3 = motorsito.crearNodo(nodoTrans8,malla3,"malla3");



    TNodo* nodoTrans9 = motorsito.crearNodo(motorsito.getRaiz(),transf9, "Trans9");
    TNodo* nodoTrans10 = motorsito.crearNodo(nodoTrans9,transf10, "Trans10");
//   TNodo* nodoMalla4 = motorsito.crearNodo(nodoTrans10,malla4,"malla4");



    TNodo* nodoTrans11 = motorsito.crearNodo(motorsito.getRaiz(),transf11, "Trans11");
    TNodo* nodoTrans12 = motorsito.crearNodo(nodoTrans11,transf12, "Trans12");
    //TNodo* nodoMalla5 = motorsito.crearNodo(nodoTrans12,malla5,"malla5");



    TNodo* nodoTrans13 = motorsito.crearNodo(motorsito.getRaiz(),transf13, "Trans13");
    TNodo* nodoTrans14 = motorsito.crearNodo(nodoTrans13,transf14, "Trans14");
   // TNodo* nodoMalla6 = motorsito.crearNodo(nodoTrans14,malla6,"malla6");

    //motorsito.transformarMalla(nodoMalla6,2.75,glm::vec3(0,1,0));
    //motorsito.transformarMalla(nodoMalla6,0,glm::vec3(3,0,0));

//    motorsito.transformarMalla(nodoMalla4,0,glm::vec3(0,0,-5));

    TNodo* mallaPrueba= motorsito.crearObjetoMallaCompleto(motorsito.getRaiz(),"./res/Oso.obj", "Oso Prueba");
    TNodo* mallaPrueba2= motorsito.crearObjetoMallaCompleto(mallaPrueba->getPadre(),"./res/andador.obj", "andador Prueba");
    TNodo* mallaPrueba3= motorsito.crearObjetoMallaCompleto(motorsito.getRaiz(),"./res/Oso.obj", "Oso Prueba 2 ");

    motorsito.TrasladarObjeto(mallaPrueba3,glm::vec3(20,0,0));
    motorsito.cambiarNodoOrigen(mallaPrueba2,mallaPrueba3->getPadre());

    motorsito.registrarCamara(nodoCamara1);
    motorsito.activarCamara(nodoCamara1);

    motorsito.registrarCamara(nodoCamara2);
    //motorsito.activarCamara(nodoCamara2);
    /*Funciones de la fachada*/

    motorsito.obtenerMatCam();

    int malla=0;//Borrar y volver a cambiar update de display a void
    int actual =0; //Borrar y volver a cambiar update de display a void
   int estado=0; //Borrar
    int cont=0; //Borrar

    int cami=1; //Borrar
    int camaraActual=0; //Borrar
    float alberto=0; //Borrar
    int contador=0;
    glm::vec3 traslado=glm::vec3(0,0,0); //Borrar
    motorsito.verMallas(nodoMalla1);
    motorsito.verRecursos();
    while(!motorsito.IsClosed()){
        motorsito.Clear(0.0f,0.15f,0.3f,1.0f);
       shader.Bind();

       motorsito.draw(&shader);
       alberto++;
       if(alberto>=10){
        motorsito.animarMalla(nodoMalla1);
        alberto=0;}
       malla= motorsito.UpdateDisplay();

       /*Prueba para LOD*/



       /***********/

/*Esto ira fuera*/

/**/        if(malla ==0){
            if(actual!=0){
               //      motorsito.cambiarMalla(malla1, "./res/andador1.obj");
              //  std::cout<<"SIN MALLA"<<std::endl;
                   motorsito.cambiarNodoOrigen(mallaPrueba2,mallaPrueba3->getPadre());

                actual=0;
            }
        }else if(malla==1){
             if(actual!=1){
           //   motorsito.cambiarMalla(malla1, "./res/andador2.obj");
                motorsito.TrasladarObjeto(mallaPrueba3,glm::vec3(1,0,0));
                actual=1;
             }
        }else if(malla==2){
             if(actual!=2){
          //     motorsito.cambiarMalla(malla1, "./res/bear.obj");
          //        motorsito.cambiarMalla(malla1, "./res/andador3.obj");
                          motorsito.TrasladarObjeto(mallaPrueba2,glm::vec3(1,0,0));

                actual=2;
             }
        }else if(malla==3){
             if(actual!=3){
               //motorsito.cambiarMalla(malla1, "./res/andador4.obj");
                   motorsito.cambiarNodoOrigen(mallaPrueba2,motorsito.getRaiz());

               actual=3;
             }
        }

        //motorsito.verMallas(nodoMalla1);
      //  motorsito.animarMalla(nodoMalla1);
            if(cami==1){
                if(camaraActual!=1){
                    camaraActual=1;
                    motorsito.activarCamara(nodoCamara1);
                }
            }else{
                if(camaraActual!=2){
                    camaraActual=2;
                    motorsito.activarCamara(nodoCamara2);
                }
            }
/*Esto ira fuera*/

if(estado==0){
traslado.x=0.01;
cont++;
    if(cont==100){
        estado=1;
        cont=-100;
    }
}else{
traslado.x= (-0.01);
cont++;
    if(cont==100){
        estado=0;
        cont=-100;
    }
}
//std::cout<<traslado.x<<std::endl;
//transf3->rotar(0.01,glm::vec3(0,0,1));
//transf4->trasladar(traslado);
motorsito.transformarEntidad(transf4,0,traslado);/*
if(alberto>=4){
//                std::cout<<"YI"<<cami<<std::endl;

    if(camaraActual==1){
     //       std::cout<<"YO "<<cami<<std::endl;

       // cami=2;
        // std::cout<<"CAMBIO a camara "<<cami<<std::endl;
    }if(camaraActual==2){
        std::cout<<"CAMBIO a camara"<<cami<<std::endl;
        cami=1;
    }
    alberto=0;
}*/
//alberto++;
//alberto=alberto+0.01;
//std::cout<<"AL "<<alberto<<" Camara "<<cami<<std::endl;

}
/*
    delete(transf1);
    delete(transf2);*/
    delete(malla1);
    /*delete(malla2);
    delete(cam);
    delete(nodoTrans1);
    delete(nodoTrans2);
    delete(nodoMalla1);
*/
    std::cout << "Bye world!" << std::endl;
    return 0;
}
