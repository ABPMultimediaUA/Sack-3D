#include <iostream>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <glm/glm.hpp>

#include "../include/shader.h"
#include "../include/tnodo.h"
//Entidades
#include "../include/tentidad.h"
//Recursos
//Gestor
#include "../include/tmotorbear.h"
#include "Box2D/Box2D.h"



#define WIDTH 1080
#define HEIGHT 720

using namespace std;

b2BodyDef * DinamicBodyDef(float x, float y, float angle){
        b2BodyDef * dinam = new b2BodyDef();
        dinam->type= b2_dynamicBody;
        dinam->position.Set(x,y);
        dinam->angle = angle;
        return dinam;
    }

b2BodyDef * StaticBodyDef(float x, float y, float angle){
        b2BodyDef * stat = new b2BodyDef();
        stat->type= b2_staticBody;
        stat->position.Set(x,y);
        stat->angle = angle;
        return stat;
    }

b2PolygonShape * crearShape(float x, float y){
        b2PolygonShape* polyShape = new b2PolygonShape ;
        polyShape->SetAsBox(x, y);
        return polyShape;
    }



b2FixtureDef* CrearFixture(b2PolygonShape* shape, float density, float restitution){

        b2FixtureDef * fixture = new b2FixtureDef();
        fixture->shape=shape;
        fixture->density= density;
        fixture->restitution=restitution;
        return fixture;
}

int main(int argc, char* argv[])
{

    TMotorBear motorsito(WIDTH, HEIGHT, "Bear Engine");
const b2Color verde(0,1,0);
int32 cuatro = 4;
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity,true);
    //Shader shader("./res/basicShaderToon");
   // Shader shader("./res/basicShaderToon");
motorsito.crearMalla("./res/cubo.obj",0);
//Camara
    TNodo* nodoCam= motorsito.crearObjetoCamaraCompleto(motorsito.getRaiz(),"Camara",glm::vec3(0,0,10), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f,1000.0f);
    //   motorsito.transformarEntidad(nodoCam->getPadre()->getEntidad(),0.0f,glm::vec3(0,5,30));
 //motorsito.TrasladarObjeto(nodoCam,glm::vec3(0,0,));
    motorsito.activarCamara(nodoCam);


//TTransform* transLuzD = static_cast<TTransform*> (nodoLuzDiff->getPadre()->getEntidad());
  //TNodo* nodoMallaLuz = motorsito.crearObjetoMallaCompleto(motorsito.getRaiz(),"./res/cubo.obj","Cubo Pos camara");
 //   motorsito.EscalarObjeto(nodoMallaLuz,glm::vec3(0.2,0.2,0.2));

   // TNodo* nodoLuzDiff = motorsito.crearObjetoLuz(nodoMallaLuz->getPadre(),glm::vec3(1.0f,1.0f,1.0f), glm::vec3(0,0,0),"lightUno", 1);//glm::vec3(5.0f,0.0f,-1.0f),"lightDiff", 1);
   // TNodo* nodoLuzDiff = motorsito.crearObjetoLuz(motorsito.getRaiz(),glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0,0,0),"lightDiff", 1);//glm::vec3(5.0f,0.0f,-1.0f),"lightDiff", 1);

   // motorsito.TrasladarObjeto(nodoMallaLuz, glm::vec3(5,5,5));
    /*TNodo* MallaHud = motorsito.crearObjetoMallaCompleto(nodoCam->getPadre(),"./res/cubo.obj","Cubo HUD");
     motorsito.TrasladarObjeto(MallaHud,glm::vec3(0,-1.5,-3));
     motorsito.EscalarObjeto(MallaHud, glm::vec3(2.5,1,0.01));
*/
////////
    b2BodyDef* cuboCae = DinamicBodyDef(1,50 ,0); //Cubo que cae
    b2BodyDef* cuboStatico = StaticBodyDef(0,0,0);
    b2BodyDef* cuboSuelo = StaticBodyDef(5,-2,0);

    b2Body* staticBody = world.CreateBody(cuboStatico);
    b2Body* staticBodySu = world.CreateBody(cuboSuelo);
    b2Body* dinamicBody = world.CreateBody(cuboCae);

    b2PolygonShape * staticShape = crearShape(1,2.5);
    b2PolygonShape * sueloShape = crearShape(600,1);
    b2PolygonShape * dinamicShape = crearShape(1,1);

    staticBody->CreateFixture(CrearFixture(staticShape, 1, 0));
    staticBodySu->CreateFixture(CrearFixture(sueloShape, 1, 0));
    dinamicBody->CreateFixture(CrearFixture(dinamicShape, 1, 0.1));

    TNodo* malla = motorsito.crearObjetoMallaCompleto(motorsito.getRaiz(),"./res/andador0.obj","Humano Estatico 0",1);
    motorsito.cambiarMalla(malla->getEntidad(),"./res/andador1b.obj");
    motorsito.cambiarMalla(malla->getEntidad(),"./res/andador2.obj");
    motorsito.cambiarMalla(malla->getEntidad(),"./res/andador3.obj");
    motorsito.cambiarMalla(malla->getEntidad(),"./res/andador0.obj");
   /* motorsito.cambiarMalla(malla->getEntidad(),"./res/andador4.obj");
    motorsito.cambiarMalla(malla->getEntidad(),"./res/andador5.obj");
    motorsito.cambiarMalla(malla->getEntidad(),"./res/andador6.obj");
    motorsito.cambiarMalla(malla->getEntidad(),"./res/andador7.obj");
    motorsito.cambiarMalla(malla->getEntidad(),"./res/andador8.obj");
    motorsito.cambiarMalla(malla->getEntidad(),"./res/andador0.obj");*/
    motorsito.TrasladarObjeto(malla,glm::vec3(staticBody->GetPosition().x ,staticBody->GetPosition().y,0));
    motorsito.EscalarObjeto(malla,glm::vec3(1,1,1.0));


 //   TNodo* mallaD = motorsito.crearObjetoMallaCompleto(motorsito.getRaiz(),"./res/andador1.obj","Humano Estatico 1",0);
 //   TNodo* mallaT = motorsito.crearObjetoMallaCompleto(motorsito.getRaiz(),"./res/andador2.obj","Humano Estatico 2",0);
  //  TNodo* mallaC = motorsito.crearObjetoMallaCompleto(motorsito.getRaiz(),"./res/cubo.obj","cubo Estatico",0);

//    motorsito.TrasladarObjeto(mallaD,glm::vec3(staticBody->GetPosition().x -2 ,staticBody->GetPosition().y,0));

//    motorsito.TrasladarObjeto(mallaT,glm::vec3(staticBody->GetPosition().x +2 ,staticBody->GetPosition().y,0));
//    motorsito.TrasladarObjeto(mallaC,glm::vec3(staticBody->GetPosition().x ,staticBody->GetPosition().y+5,0));




  //  motorsito.RotarObjeto(cub,glm::vec3(0,45,0));

  //   motorsito.RotarObjeto(malla,glm::vec3(0,glm::radians(45.0),0));
/*
    TNodo* mallaSu = motorsito.crearObjetoMallaCompleto(motorsito.getRaiz(),"./res/cubo.obj","Suelo Estatico");
    motorsito.TrasladarObjeto(mallaSu,glm::vec3(staticBodySu->GetPosition().x ,staticBodySu->GetPosition().y,0));*/
  // motorsito.EscalarObjeto(mallaSu,glm::vec3(600.0,1,1.0));

/*
    TNodo* mallaD = motorsito.crearObjetoMallaCompleto(motorsito.getRaiz(),"./res/cubo.obj","Humano Dinamico");
    motorsito.EscalarObjeto(mallaD,glm::vec3(1,1,1.0f));
    motorsito.TrasladarObjeto(mallaD,glm::vec3(dinamicBody->GetPosition().x ,dinamicBody->GetPosition().y,0));
*/
    /*Tamanyo que ocupa el objeto*/
   /* TNodo* mallaPro = motorsito.crearObjetoMallaCompleto(malla->getPadre(), "./res/cubo.obj", "CuboLargo");
    motorsito.EscalarObjeto(mallaPro,glm::vec3(1,2.5,1.0f));
   motorsito.TrasladarObjeto(mallaPro,glm::vec3(0,0,-2));*/
 //   motorsito.RotarObjeto(mallaPro,glm::vec3(0,glm::radians(-90.0),0));

  //  motorsito.cambiarNodoOrigen(mallaPro,malla->getPadre());

  /*  TNodo* mallaProD = motorsito.crearObjetoMallaCompleto(mallaD->getPadre(), "./res/cubo.obj", "CuboLargo");
    motorsito.EscalarObjeto(mallaProD,glm::vec3(1,1,1.0f));
    motorsito.RotarObjeto(mallaProD,glm::vec3(0,glm::radians(-90.0),0));

*/
    /*c*****************************/

  //  TTransform * trans = static_cast<TTransform*>(mallaD->getPadre()->getEntidad());
  //  TTransform * transS = static_cast<TTransform*>(mallaSu->getPadre()->getEntidad());
  //  glm::vec3 posT = trans->GetPos();
  //  glm::vec3 posS = transS->GetPos();
   float i=0;
   std::cout<<std::endl;
   motorsito.verArbol();

   motorsito.verDetallesTransformaciones(nodoCam->getPadre());
   motorsito.verDetallesTransformaciones(malla->getPadre());
//   motorsito.verDetallesTransformaciones(mallaD->getPadre());
motorsito.verArbol();
   motorsito.verMallas(malla);
//   motorsito.verMallas(mallaD);
 int alberto =0;
 int mostrado=1;
 int mesh=0;
 int cami=0;

// transLuz = static_cast<TTransform*> (nodoLuzDiff->getPadre()->getEntidad());
 //luzDif = static_cast<TLuz*> (nodoLuzDiff->getEntidad());
   std::cout<<std::endl;
   motorsito.asignarTextura(malla,"./res/andaT.png");
   //motorsito.asignarTextura(mallaT,"./res/player.png");
//   motorsito.asignarTextura(mallaC,"./res/player.png");
    //motorsito.asignarMaterial(malla,"Rojo");
    while(!motorsito.IsClosed()){
         motorsito.Clear(0.0f,0.15f,0.3f,1.0f);

         world.Step(1/20.0,8,3);

       // motorsito.RotarObjeto(mallaPro,glm::vec3(0,0,i)); //Prueba transformacion local-global
      //  std::cout<<luzDif->getPos().x<<" "<<luzDif->getPos().y<<" "<<luzDif->getPos().z<<" "<<std::endl;
    //   std::cout<<transLuz->GetPos().x<<" "<<transLuz->GetPos().y<<" "<<transLuz->GetPos().z<<" "<<std::endl;
      /*  motorsito.RotarObjeto(mallaD,glm::vec3(0,0,dinamicBody->GetAngle()));
        motorsito.TrasladarObjeto(mallaD,glm::vec3(dinamicBody->GetPosition().x ,dinamicBody->GetPosition().y,0));*/

/* Ejecutable animacion
       if(alberto==15){
            motorsito.animarMalla(malla);
            alberto=0;
               motorsito.verMallas(malla);
        }*/

       // colo=colo+0.01;
        //motorsito.draw(&shader);
        motorsito.draw();
    motorsito.UpdateDisplay();


      // if(motorsito.UpdateDisplay()==5){
      /* if(mesh==5){
            if(mostrado){
            motorsito.hacerInvisibleObjeto(malla);
          //  mesh=0;
            mostrado=0;
            motorsito.verArbol();
            }
       }
        if(mesh==6){
            if(!mostrado){
            motorsito.hacerVisibleObjeto(malla);
          //  mesh=0;
            mostrado=1;
            motorsito.verArbol();
            }
       }*/
        alberto++;
    }
    delete(cuboCae);
    delete(cuboStatico);
    delete(cuboSuelo);

    delete(staticShape);
    delete(sueloShape);
    delete(dinamicShape);
    return 0;
}
