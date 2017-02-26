#ifndef TNODO_H
#define TNODO_H

#include<vector>
#include<iostream>
#include "tentidad.h"
#include "shader.h"
#include <glm/glm.hpp>

class TNodo
{
    public:
        TNodo(int cepa);
        virtual ~TNodo();

        int addHijo(TNodo* hijo);
        int remHijo(TNodo* hijo);
        bool setEntidad(TEntidad * entity );
        void setNombreEntidad(char* name);
        char* getNombreEntidad();
        TEntidad* getEntidad();
        TNodo* getPadre();
        int esRaiz();
        void draw(Shader* shad, glm::mat4 cam);
    protected:

    private:
        int raiz;
        TEntidad * entidad;
        char* nombreEntidad;
        std::vector<TNodo*> hijos;
        TNodo* padre;


};

#endif // TNODO_H
