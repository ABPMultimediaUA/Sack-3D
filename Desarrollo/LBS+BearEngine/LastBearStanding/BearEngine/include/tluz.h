#ifndef TLUZ_H
#define TLUZ_H

#include "../include/tentidad.h"
#include <glm/glm.hpp>
#include "../include/shader.h"
class TLuz : public TEntidad
{
    public:
        TLuz(float x, float y, float z, char* name );
        virtual ~TLuz();
        void setIntensidad(glm::vec3 colr);
        glm::vec3 getIntensidad();
        void setPosicion(float x, float y,float z);

        void begingDraw(Shader* shad, std::vector<glm::mat4>* pila);
        void endDraw(std::vector<glm::mat4>* pila);
        int getTipo();

    protected:

    private:

    glm::vec3 intensidad; //Color;
    glm::vec3 posicion;
    int tipo;
    char * nombreLuz;
};

#endif // TLUZ_H
