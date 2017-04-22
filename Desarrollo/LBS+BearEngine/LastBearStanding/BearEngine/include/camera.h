#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "../include/tentidad.h"

class Camera : public TEntidad
{
    public:
        Camera(){
            tipo=2;
            activada=0;
        }
        Camera(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar){
           m_perspective = glm::perspective(fov, aspect, zNear, zFar);
           esPerspectiva=1;
         //m_paralela = glm::ortho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);

            m_position = pos;
            m_forward = glm::vec3(0,0,1);
            m_up = glm::vec3(0,1,0);
            tipo=2;
            activada=0;
        }
          virtual ~Camera(){}

        inline glm::mat4 GetViewProjection() const{
            if(esPerspectiva) return m_perspective * glm::lookAt(m_position, m_position+ m_forward, m_up );
            return m_paralela * glm::lookAt(m_position, m_position+ m_forward, m_up );
        }
        inline glm::mat4 getPers() const{
            return m_perspective;
        }
        glm::mat4 miraA(glm::vec3 pos, glm::vec3 direccion, glm::vec3 up);
        void setPerspectiva(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar);
        void setParalela(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar);
         inline glm::vec3& GetPosition() {return m_position;}
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
        glm::vec3 m_position;
        glm::vec3 m_forward;
        glm::vec3 m_up;
        int tipo;
        int esPerspectiva;
        int activada;
};

#endif // CAMERA_H
