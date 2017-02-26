#ifndef TENTIDAD_H
#define TENTIDAD_H

#include"glm/glm.hpp"
#include <vector>
#include "shader.h"
class TEntidad
{
    public:
        static std::vector<glm::mat4>* pila;
        virtual ~TEntidad(){}
        virtual void begingDraw(Shader* shad, glm::mat4 matCam) =0;
        virtual void endDraw()  =0;
        virtual int getTipo()=0;

    protected:

    private:
};

#endif // TENTIDAD_H
