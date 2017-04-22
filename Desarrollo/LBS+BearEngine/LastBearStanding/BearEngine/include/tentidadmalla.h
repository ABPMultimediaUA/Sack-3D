#ifndef TENTIDADMALLA_H
#define TENTIDADMALLA_H

#include "../include/tentidad.h"
#include "../include/mesh.h"


class TEntidadMalla : public TEntidad
{
    public:
        TEntidadMalla();
        virtual ~TEntidadMalla();
        void begingDraw(Shader* shad, std::vector<glm::mat4>* pila);
        void endDraw(std::vector<glm::mat4>* pila);
        void animar();
        int getTipo();
        void verMallas();

        void setName(char * name);


        //void setRecurso();
        void setMalla(Mesh* azteca);
//      void setMallas(std::vector<Mesh*>* aztecas);

      void activarMalla(int i);
      void verInformacionEMalla();

    protected:

    private:
        int tipo;
        Mesh* mesh;
        std::vector<Mesh*> meshes;
        int activo;

};

#endif // TENTIDADMALLA_H
