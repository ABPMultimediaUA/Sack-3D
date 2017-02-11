#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include "tentidad.h"
//#include "obj_loader.h"
#include "modeloindexado.h"

class Vertex {

    public:
        Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0,0,0)){
            this->pos       =   pos;
            this->texCoord  =   texCoord;
            this->normal    =   normal;
        }
        inline glm::vec3* getPos() {return&pos;}
        inline glm::vec2* getTexCoord() {return&texCoord;}
        inline glm::vec3* getNormal() {return&normal;}
    protected:
    private:
        glm::vec3 pos;
        glm::vec2 texCoord;
        glm::vec3 normal;
};

class Mesh : public TEntidad
{
    public:
     //   Mesh();
        Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
      //  void Crear(Vertex* vertices, unsigned int numVertices);
   //     Mesh( const std::string& fileName);
        Mesh( );
        void Draw();
        void begingDraw();
        void endDraw();
        int getTipo();
        virtual ~Mesh();
        void InitMesh(const modeloIndexado& model);

    protected:

    private:
        Mesh(const Mesh& other){}
        void operator=(const Mesh& other){}
        //void InitMesh(const IndexedModel& model);

        enum{
            POSITION_VB,
            TEXCOORD_VB,
            NORMAL_VB,

            INDEX_VB,

            NUM_BUFFERS
        };

        int tipo;
        GLuint m_vertexArrayObject;
        GLuint m_vertexArrayBuffers[NUM_BUFFERS];
        unsigned int m_drawCount;

};

#endif // MESH_H
