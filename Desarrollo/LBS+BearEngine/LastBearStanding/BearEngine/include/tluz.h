#ifndef TLUZ_H
#define TLUZ_H

#include "../include/tentidad.h"
#include <glm/glm.hpp>
#include "../include/shader.h"
class TLuz : public TEntidad
{
    public:
        TLuz(float x, float y, float z, char* name, int tipe );
        virtual ~TLuz();
        void setIntensidad(glm::vec3 colr);
        glm::vec3 getIntensidad();
        void setPosicion(float x, float y,float z);

        void begingDraw(Shader* shad, std::vector<glm::mat4>* pila);
        void endDraw(std::vector<glm::mat4>* pila);
        void aplicarLuz(Shader* shad, glm::vec3 pos);
        int getTipo();
        glm::vec3 getPos();
    protected:

    private:

    glm::vec3 intensidadA; //Color;
    glm::vec3 intensidadD; //Color;
    glm::vec3 posicion;
    int tipo;
    int luzType; //0 Ambiente, 1 difusa, 2 especular
    char * nombreLuz;
};

#endif // TLUZ_H
