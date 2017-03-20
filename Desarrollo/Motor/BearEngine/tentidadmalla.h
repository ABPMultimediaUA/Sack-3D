#ifndef TENTIDADMALLA_H
#define TENTIDADMALLA_H

#include "tentidad.h"
#include "mesh.h"


class TEntidadMalla : public TEntidad
{
    public:
        TEntidadMalla();
        virtual ~TEntidadMalla();
        void begingDraw(Shader* shad, std::vector<glm::mat4>* pila);
        void endDraw(std::vector<glm::mat4>* pila);
        int getTipo();

        //void setRecurso();
        void setMalla(Mesh* azteca);
//      void setMallas(std::vector<Mesh*>* aztecas);

      void activarMalla(int i);

    protected:

    private:
        int tipo;
        Mesh* mesh;
        std::vector<Mesh*> meshes;
        int activo;
};

#endif // TENTIDADMALLA_H
