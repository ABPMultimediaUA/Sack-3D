#include <iostream>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "tnodo.h"
//Entidades
#include "tentidad.h"
//Recursos
//Gestor
#include "tmotorbear.h"
#include "Box2D/Box2D.h"
#include "foodraw.h"



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
    Shader shader("./res/basicShaderLuz");
motorsito.crearMalla("./res/cubo.obj");
//Camara
    TNodo* nodoCam= motorsito.crearObjetoCamaraCompleto(motorsito.getRaiz(),"Camara",glm::vec3(0,0,-4), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f,1000.0f);
 //   motorsito.transformarEntidad(nodoCam->getPadre()->getEntidad(),0.0f,glm::vec3(0,5,30));
 motorsito.TrasladarObjeto(nodoCam,glm::vec3(0,5,800));
    motorsito.activarCamara(nodoCam);
    TNodo* MallaHud = motorsito.crearObjetoMallaCompleto(nodoCam->getPadre(),"./res/cubo.obj","Cubo HUD");
     motorsito.TrasladarObjeto(MallaHud,glm::vec3(0,-1.5,-3));
     motorsito.EscalarObjeto(MallaHud, glm::vec3(2.5,1,0.01));

////////



    b2BodyDef* cuboCae = DinamicBodyDef(30,500,0); //Cubo que cae
    b2BodyDef* cuboStatico = StaticBodyDef(0,0,0);
    b2BodyDef* cuboSuelo = StaticBodyDef(5,-6,0);

    b2Body* staticBody = world.CreateBody(cuboStatico);
    b2Body* staticBodySu = world.CreateBody(cuboSuelo);
    b2Body* dinamicBody = world.CreateBody(cuboCae);

    b2PolygonShape * staticShape = crearShape(15,37);
    b2PolygonShape * sueloShape = crearShape(600,10);
    b2PolygonShape * dinamicShape = crearShape(15,37);

    staticBody->CreateFixture(CrearFixture(staticShape, 1, 0));
    staticBodySu->CreateFixture(CrearFixture(sueloShape, 1, 0));
    dinamicBody->CreateFixture(CrearFixture(dinamicShape, 1, 0.1));

    TNodo* malla = motorsito.crearObjetoMallaCompleto(motorsito.getRaiz(),"./res/Oso.obj","Oso Estatico");
    motorsito.TrasladarObjeto(malla,glm::vec3(staticBody->GetPosition().x ,staticBody->GetPosition().y,0));
    motorsito.EscalarObjeto(malla,glm::vec3(1,1,1.0));

    TNodo* mallaSu = motorsito.crearObjetoMallaCompleto(motorsito.getRaiz(),"./res/cubo.obj","Suelo Estatico");
    motorsito.TrasladarObjeto(mallaSu,glm::vec3(staticBodySu->GetPosition().x ,staticBodySu->GetPosition().y,0));
   motorsito.EscalarObjeto(mallaSu,glm::vec3(600.0,10,20.0));


    TNodo* mallaD = motorsito.crearObjetoMallaCompleto(motorsito.getRaiz(),"./res/OsoDos.obj","Oso Dinamico");
    motorsito.EscalarObjeto(mallaD,glm::vec3(1,1,1.0f));
    motorsito.TrasladarObjeto(mallaD,glm::vec3(dinamicBody->GetPosition().x ,dinamicBody->GetPosition().y,0));

    TNodo* mallaPro = motorsito.crearObjetoMallaCompleto(mallaD->getPadre(), "./res/cubo.obj", "CuboLargo");
    motorsito.EscalarObjeto(mallaPro,glm::vec3(100,1,1.0f));


    TTransform * trans = static_cast<TTransform*>(mallaD->getPadre()->getEntidad());
    TTransform * transS = static_cast<TTransform*>(mallaSu->getPadre()->getEntidad());
    glm::vec3 posT = trans->GetPos();
    glm::vec3 posS = transS->GetPos();
   float i=0;
    while(!motorsito.IsClosed()){
         motorsito.Clear(0.0f,0.15f,0.3f,1.0f);

         world.Step(1/20.0,8,3);

        i = i+0.01;
        motorsito.RotarObjeto(mallaPro,glm::vec3(0,0,i)); //Prueba transformacion local-global

        motorsito.RotarObjeto(mallaD,glm::vec3(0,0,dinamicBody->GetAngle()));
        motorsito.TrasladarObjeto(mallaD,glm::vec3(dinamicBody->GetPosition().x ,dinamicBody->GetPosition().y,0));
        shader.Bind();

        motorsito.draw(&shader);
        motorsito.UpdateDisplay();
    }
    delete(cuboCae);
    delete(cuboStatico);
    delete(cuboSuelo);

    delete(staticShape);
    delete(sueloShape);
    delete(dinamicShape);



    cout << "Hello world!" << endl;
    return 0;
}
