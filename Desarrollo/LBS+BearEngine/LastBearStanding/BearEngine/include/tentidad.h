#ifndef TENTIDAD_H
#define TENTIDAD_H

#include"glm/glm.hpp"
#include <vector>
#include "../include/shader.h"
class TEntidad
{
    public:
       // static std::vector<glm::mat4>* pila;
        virtual ~TEntidad(){}
        virtual void begingDraw(Shader* shad, std::vector<glm::mat4>* pila) =0;
        virtual void endDraw(std::vector<glm::mat4>* pila)  =0;
        virtual int getTipo()=0;


    protected:

    private:
};

#endif // TENTIDAD_H
