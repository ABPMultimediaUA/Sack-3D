#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "tentidad.h"

class Camera : public TEntidad
{
    public:
        Camera(){}
        Camera(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar){
            m_perspective = glm::perspective(fov, aspect, zNear, zFar);
            m_position = pos;
            m_forward = glm::vec3(0,0,1);
            m_up = glm::vec3(0,1,0);
            tipo=2;
        }

        inline glm::mat4 GetViewProjection() const{
            return m_perspective * glm::lookAt(m_position, m_position+ m_forward, m_up );
        }

         inline glm::vec3& GetPosition() {return m_position;}
           void begingDraw(Shader* shad, glm::mat4 matCam);
        void endDraw();
        int getTipo();
    protected:
    private:
        glm::mat4 m_perspective;
        glm::vec3 m_position;
        glm::vec3 m_forward;
        glm::vec3 m_up;
        int tipo;
};

#endif // CAMERA_H
