#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif // GLEW_STATIC
#include "../include/modeloindexado.h"
#include "trecurso.h"
#include "tmaterial.h"

#include <assimp/scene.h>
#include <assimp/mesh.h>

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

class Mesh : public TRecurso
{
    public:
     //   Mesh();
      //  void Crear(Vertex* vertices, unsigned int numVertices);

        Mesh(float ancho, float alto, float prof);
        Mesh( const char* fileName);
        Mesh( );
        void Draw();
        virtual ~Mesh();
        char* GetNombre();
        int GetTipo();
        void setNombre( char* name);
        void setTipo(int tipo);
        void asignarMatM(TMaterial* m);
    protected:

    private:
        struct EntradaMalla{

          public:

           EntradaMalla(aiMesh *mesh, const aiScene* scene);
           EntradaMalla(float ancho, float alto, float prof);
            void asignarMatEM(TMaterial* m);
           ~EntradaMalla();
           void InitMesh(const modeloIndexado& model);
            void Draw();
          private:
            enum{
                POSITION_VB,
                TEXCOORD_VB,
                NORMAL_VB,
                INDEX_VB,

                NUM_BUFFERS
            };

         //   void processMesh(aiMesh* mesh, const aiScene* scene)
            //void clear(){}
            GLuint m_vertexArrayObject;
            GLuint m_vertexArrayBuffers[NUM_BUFFERS];
            unsigned int m_drawCount;


        };

        std::vector<EntradaMalla*> MallasLeidas;
        char* nombre;
        int type;
        Mesh(const Mesh& other){}
        void operator=(const Mesh& other){}

        //void InitMesh(const IndexedModel& model);


       // int tipo;
};

#endif // MESH_H
