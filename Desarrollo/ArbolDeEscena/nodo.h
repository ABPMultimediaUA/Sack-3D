#ifndef NODO_H
#define NODO_H
#include <vector>
#include "tentidad.h"

#include "shader.h"
#include "camera.h"
#include "transform.h"


class Nodo
{
    public:
        Nodo(int raiz);
        virtual ~Nodo();
        int addHijo(Nodo* hijo);
        int remHijo(Nodo* hijo);
        bool seTEntidad(TEntidad* entidadN);
        TEntidad *getEntidad();
        int conPadre();
        Nodo* getPadre();
        void draw(Shader* shad, Camera* cam, Transform* trans);
        void setPadre(Nodo* padreN);
        int numeroHijos();
        void setRaiz(int i);
    protected:

    private:
        TEntidad * entidad;
        std::vector <Nodo*> hijos;
        Nodo* padre;
        int tienePadre;
        int esRaiz;
};

#endif // NODO_H
