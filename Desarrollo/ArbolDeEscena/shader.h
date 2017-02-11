#ifndef SHADER_H
#define SHADER_H


#define GLEW_STATIC
#include <GL/glew.h>
//#include "transform.h"
//#include "camera.h"
#include <string>
#include"transform.h"
#include"camera.h"



class Shader
{
    public:
     //   Shader();

        Shader(const std::string& fileName);

        void Bind();
        void Update(const Transform* transform, const Camera* camera);
       // void Crear(const std::string& fileName);


        virtual ~Shader();

        int positionLocation;

    protected:

    private:
        static const unsigned int NUM_SHADERS = 2;
        Shader(const Shader& other){}
        void operator=(const Shader& other){}

        enum{
            TRANSFORM_U,


            NUM_UNIFORMS
        };

        GLuint m_program;
        GLuint m_shaders[NUM_SHADERS];
        GLuint m_uniforms[NUM_UNIFORMS];
};


#endif // SHADER_H
