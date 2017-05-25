#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "../include/tentidad.h"

class Camera : public TEntidad
{
    public:
        Camera();
        Camera( float fov, float aspect, float zNear, float zFar);
        virtual ~Camera(){}
        inline glm::mat4 getPers() const{
            return m_perspective;
        }
        glm::mat4 miraA(glm::vec3 pos, glm::vec3 direccion, glm::vec3 up);
        void setPerspectiva(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar);
        void setParalela(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar);  
        void begingDraw(Shader* shad, std::vector<glm::mat4>* pila);
        void endDraw(std::vector<glm::mat4>* pila);
        void activarCamara();
        void desactivarCamara();
        int verActivadoCamara();

        int getTipo();
    protected:
    private:
        glm::mat4 m_perspective;
        glm::mat4 m_paralela;
        glm::vec3 m_forward;
        glm::vec3 m_up;
        int tipo;
        int esPerspectiva;
        int activada;
};

#endif // CAMERA_H
