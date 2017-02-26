#ifndef TENTIDADMALLA_H
#define TENTIDADMALLA_H

#include "tentidad.h"
#include "mesh.h"


class TEntidadMalla : public TEntidad
{
    public:
        TEntidadMalla();
        virtual ~TEntidadMalla();
        void begingDraw(Shader* shad, glm::mat4 matCam);
        void endDraw();
        int getTipo();

        //void setRecurso();
        void setMalla(Mesh* azteca);
      // void setMallas(std::vector<Mesh*>* aztecas);

    protected:

    private:
        int tipo;
        Mesh* mesh;
       // std::vector<Mesh*>* meshes;
};

#endif // TENTIDADMALLA_H
