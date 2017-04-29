#ifndef TLUZ_H
#define TLUZ_H

#include "../include/tentidad.h"
#include <glm/glm.hpp>
#include "../include/shader.h"
class TLuz : public TEntidad
{
    public:
        TLuz();
        virtual ~TLuz();
        void setIntensidad(glm::vec3 colr);
        glm::vec3 getIntensidad();

        void begingDraw(Shader* shad, std::vector<glm::mat4>* pila);
        void endDraw(std::vector<glm::mat4>* pila);
        int getTipo();

    protected:

    private:

    glm::vec3 intensidad; //Color;
    int tipo;
};

#endif // TLUZ_H
