
#ifndef TMOTORBEAR_H
#define TMOTORBEAR_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../include/shader.h"
#include "../include/tnodo.h"
#include "../include/tgestorrecursos.h"
//Entidades
#include "../include/tentidad.h"
#include "../include/ttransform.h"
#include "../include/tentidadmalla.h"
#include "camera.h"
#include "../include/tluz.h"
//Recursos
#include "trecurso.h"
#include "../include/mesh.h"

//Display
#include "display.h"




class TMotorBear
{
    public:
        TMotorBear(int width, int height, const std::string& title);
        virtual ~TMotorBear();

        TNodo* getRaiz();
        TNodo* crearNodo(TNodo* padre, TEntidad * ent, char* nom);
    //Debug
        void verArbol();


////OBjetos (Alto Nivel del Motor)
        TNodo* crearObjetoMallaCompleto(TNodo* padre, char * filename,  char * name);
        TNodo* crearObjetoCamaraCompleto(TNodo* padre, char * name, const glm::vec3 pos, float fov, float aspect, float zNear, float zFar);


        void RotarObjeto(TNodo* malla,glm::vec3 vec);
        void EscalarObjeto(TNodo* malla,glm::vec3 vec);
        void TrasladarObjeto(TNodo* malla,glm::vec3 vec);

        void cambiarNodoOrigen(TNodo* nodoObjeto, TNodo* PadreNuevo);
        void reiniciarTransPropias(TNodo* nodoMalla);


        void reiniciarPosicion(TNodo* nodoMalla);
        void reiniciarRotacion(TNodo* nodoMalla);
        void reiniciarEscalado(TNodo* nodoMalla);


////////(BAJO NIVEL DEL MOTOR)


        TNodo* obtenerTransformacion(TNodo* nodoMalla);
        TNodo* crearTransObj(TNodo* padre, char* name);
      //   void ReinciarTrans(TNodo* nodoTrans);

/////////////////////Transformaciones
        TEntidad * crearTransform();
   //     void transformarEntidad(TEntidad* entity, float tipo, glm::vec3 vec);
    //    void escalarEntidad(TEntidad* entity, glm::vec3 vec);
    //Debug
        void verDetallesTransformaciones(TNodo* nodoTrans);
//////////////////////////////////////////

/////////////////////Mallas
        TEntidad* crearMalla( char* file);
        TEntidad* crearMalla( float alto, float ancho, float prof);
        TNodo* crearCuboEn(float alto, float ancho, float prof, glm::vec3 vec);

        void cambiarMalla(TEntidad*, char*file);
     //   void transformarMalla(TNodo* nodoMalla, float tipo, glm::vec3 vec);//necesario que el nodo arbol este ya incorporado al arbol
        void animarMalla(TNodo* nodoMalla);
    //DEBUG
        void verMallas(TNodo* nodoMalla);

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
///////////////Gestor Recursos
        void borrarRecurso(char * nombre);
//DEBUG
        void verRecursos();
////////////////////////////////////////
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
