#ifndef TENTIDADMALLA_H
#define TENTIDADMALLA_H

#include "../include/tentidad.h"
#include "../include/mesh.h"
#include "tmaterial.h"
class Texture;

class TEntidadMalla : public TEntidad
{
    public:
        TEntidadMalla(Shader* shad);
        virtual ~TEntidadMalla();
        void begingDraw(Shader* shad, std::vector<glm::mat4>* pila);
        void endDraw(std::vector<glm::mat4>* pila);
        void animar();
        void resetAnimacion();
        int getTipo();
        void verMallas();

        void setName(char * name);

        void asignarMat(TMaterial* mat);
        //void setRecurso();
        void setMalla(Mesh* azteca);
//      void setMallas(std::vector<Mesh*>* aztecas);

      void activarMalla(int i);
      void verInformacionEMalla();
      void setTextura(TRecurso* textura);

    protected:

    private:
        int tipo;
        Mesh* mesh;
        std::vector<Mesh*> meshes;
        int activo;
        Texture* texturaM;
        TMaterial* materialM;
        Shader* shadP;

};

#endif // TENTIDADMALLA_H
