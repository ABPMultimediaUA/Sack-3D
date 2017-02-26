#ifndef TTRANSFORM_H
#define TTRANSFORM_H

#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include"tentidad.h"

class TTransform : public TEntidad
{
    public:
        TTransform();
        virtual ~TTransform();

        void identidad();
        void cargar(glm::mat4 Matriz);
        void trasponer();

        glm::mat4 GetModel() const;

        void trasladar(glm::vec3 tras);
        void rotar(float grados, glm::vec3 eje);
        void escalar(glm::vec3 scala);


        void begingDraw(Shader* shad, glm::mat4 matCam);
        void endDraw();
        int getTipo();

    protected:

    private:
        glm::mat4 m_matriz;
        int tipo;
};

#endif // TTRANSFORM_H
