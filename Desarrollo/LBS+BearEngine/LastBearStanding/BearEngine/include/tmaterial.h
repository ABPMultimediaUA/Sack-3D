#ifndef TMATERIAL_H
#define TMATERIAL_H

#include "trecurso.h"
#include "glm/glm.hpp"

class TMaterial: public TRecurso
{
    public:
        TMaterial(glm::vec3 colr, char* name);
        virtual ~TMaterial();

        char* GetNombre();
        void setNombre( char* name);
        void setTipo(int tipo);
        int GetTipo();
        void Bind();
        glm::vec3 getCol();

    protected:

    private:
        char* nombre;
        int type;
        glm::vec3 color;
        float coeficienteR;// De Momento na
};

#endif // TMATERIAL_H


