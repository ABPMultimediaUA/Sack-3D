#ifndef TMOTORBEAR_H
#define TMOTORBEAR_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "shader.h"
#include "tnodo.h"
#include "tgestorrecursos.h"
//Entidades
#include "tentidad.h"
#include "ttransform.h"
#include "tentidadmalla.h"
#include "camera.h"
#include "tluz.h"
//Recursos
#include "trecurso.h"
#include "mesh.h"

//Display
#include "display.h"




class TMotorBear
{
    public:
        TMotorBear(int width, int height, const std::string& title);
        virtual ~TMotorBear();

        TNodo* getRaiz();
        TNodo* crearNodo(TNodo* padre, TEntidad * ent, char* nom);


/////////////////////Transformaciones
        TEntidad * crearTransform();
        void transformarEntidad(TEntidad* entity, float tipo, glm::vec3 vec);
//////////////////////////////////////////

/////////////////////Mallas
        TEntidad* crearMalla( char* file);
        TEntidad* crearMalla( float alto, float ancho, float prof);
        TNodo* crearCuboEn(float alto, float ancho, float prof, glm::vec3 vec);

        void cambiarMalla(TEntidad*, char*file);
        void transformarMalla(TNodo* nodoMalla, float tipo, glm::vec3 vec);//necesario que el nodo arbol este ya incorporado al arbol

        void borrarMalla(char * nombre);

//////////////////////////////////////////

/////////////////////Camaras
        TEntidad *crearCamara(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar);
        void registrarCamara(TNodo* camera);
        TNodo* verCamaraActiva();
        void activarCamara(TNodo* cam);
//////////////////////////////////////////

/////////////////////Display
        bool IsClosed();
        void Clear(float r, float g, float b, float a);
        //void UpdateDisplay();
        int UpdateDisplay();
//////////////////////////////////////////

///////////////////////Luces
        TEntidad *crearLuz(glm::vec3 colorLuz);
        void cambiarLuz(TLuz* luz, glm::vec3 colorLuz);
        void registrarLuz(TNodo* luz);
        glm::vec3 InteLuz(int posicion);
        void activarLuces();
        void activaLuz(int numero);
//////////////////////////////////////////

        void draw(Shader* shad);
        glm::mat4 obtenerMatCam();
        //manejo de camaras, luces y viewports

    protected:

    private:
        Display* escena;
        TNodo* arbolEscena;
        TGestorRecursos* gestorRecursos;
        std::vector<TNodo*> registroCamara;
        std::vector<TNodo*>  registroLuces;
        std::vector<glm::mat4>* pila;
        TNodo* camaraActiva;
//        std::vector<Luces*> registroLuces; Cuando haya luces
        //Luces, Camaras,viewports
};

#endif // TMOTORBEAR_H
