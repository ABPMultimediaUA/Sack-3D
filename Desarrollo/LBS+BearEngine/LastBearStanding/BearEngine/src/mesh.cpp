#include "../include/mesh.h"
#include <vector>

#include <iostream>

#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>



/*
Mesh::Mesh()
{
}*/


Mesh::Mesh( const char* fileName){

    if(fileName){
    const aiScene* scene = aiImportFile(fileName,
                              aiProcess_GenSmoothNormals    |   aiProcess_Triangulate |
                              aiProcess_CalcTangentSpace    |   aiProcess_FlipUVs);


    if(scene->mFlags){
        std::cout<< "Ha habido un error al cargar el modelo "<< fileName<<std::endl;
        return;
    }

//    std::cout<< "El modelo esta compuesto por "<<scene->mRootNode->mNumChildren<<" Mallas"<<std::endl;
    for(int i =0;i< scene->mNumMeshes;i++){
        MallasLeidas.push_back( new Mesh::EntradaMalla(scene->mMeshes[i],scene));
    }
//    std::cout<< "modelo cargado con exito "<< fileName<<std::endl;
    aiReleaseImport(scene);
    }
}

Mesh::Mesh(float alto, float ancho, float prof){

    MallasLeidas.push_back( new Mesh::EntradaMalla(alto, ancho, prof));

//tipo=0;
}



Mesh::~Mesh()
{
    //glDeleteVertexArrays(1, &m_vertexArrayObject);
    //std::cout<<"Leidas: "<<MallasLeidas.size()<<std::endl;
    for(int i = 0; i< MallasLeidas.size();i++){
        delete MallasLeidas[i];
    //    std::cout<<"BORRADO"<<std::endl;
    }

    MallasLeidas.clear();
}

void Mesh::asignarMatM(TMaterial* m){
      for(int i = 0; i< MallasLeidas.size();i++){
        MallasLeidas.at(i)->asignarMatEM(m);
      }
}

char* Mesh::GetNombre(){
        return nombre;
 }
int Mesh::GetTipo(){
        return type;
 }
void  Mesh::setNombre( char* name){
    nombre= name;
}void  Mesh::setTipo(int tipo){
    type= tipo;
}
void Mesh::EntradaMalla::asignarMatEM(TMaterial* m){

}

Mesh::EntradaMalla::~EntradaMalla(){ /*INCOMPLETO */
   if(m_vertexArrayBuffers[POSITION_VB]){
   //     std::cout<<"1"<<std::endl;
           glDeleteBuffers(1, &m_vertexArrayBuffers[POSITION_VB]);}

   if(m_vertexArrayBuffers[TEXCOORD_VB]){
          //      std::cout<<"2"<<std::endl;

           glDeleteBuffers(1, &m_vertexArrayBuffers[TEXCOORD_VB]);}

   if(m_vertexArrayBuffers[NORMAL_VB]){
       // std::cout<<"3"<<std::endl;

           glDeleteBuffers(1, &m_vertexArrayBuffers[NORMAL_VB]);}

   if(m_vertexArrayBuffers[INDEX_VB]){
     //   std::cout<<"4"<<std::endl;

           glDeleteBuffers(1, &m_vertexArrayBuffers[INDEX_VB]);}

/*
   POSITION_VB,
                TEXCOORD_VB,
                NORMAL_VB,
                INDEX_VB,*/

    glDeleteVertexArrays(1, &m_vertexArrayObject);

    //glDeleteBuffers()

  //  glGenBuffers(glsizei, gluint buffers);
  //  glDeleteBuffers()
}

Mesh::EntradaMalla::EntradaMalla(aiMesh* mesh, const aiScene* scene){
    std::vector<Vertex> vertices;
    modeloIndexado model;

      for(int i=0;i<mesh->mNumVertices;i++){


        glm::vec3 position;
        glm::vec2 uV;
        glm::vec3 normal;
        position.x= mesh->mVertices[i].x;
        position.y= mesh->mVertices[i].y;
        position.z= mesh->mVertices[i].z;
        model.positions.push_back(position);
     //   uV.x=0; // Cambiar cuando texturas
       // uV.y=0; // Cambiar cuando texturas
       // model.texCoords.push_back(uV);


       if(mesh->HasTextureCoords(0)) {

			uV.x = mesh->mTextureCoords[0][i].x;
			uV.y = mesh->mTextureCoords[0][i].y;
			//std::cout<<mesh->mTextureCoords[0][i].x<<" "<<mesh->mTextureCoords[0][i].y<<std::endl;
		}else{
            uV.x=0;
            uV.y=1;
		}
		 model.texCoords.push_back(uV);


        if(mesh->HasNormals()){
            normal.x  = mesh->mNormals[i].x;
            normal.y  = mesh->mNormals[i].y;
            normal.z  = mesh->mNormals[i].z;
            model.normals.push_back(normal);
         }else{
            model.CalcNormals();
            model.normals.push_back(normal);
         }
        }
        for(int i =0; i<mesh->mNumFaces;i++){
            aiFace  face=mesh->mFaces[i];
            for(int j=0;j<face.mNumIndices;j++){ // 0..2
                model.indices.push_back(face.mIndices[j]);
            //   model.indices.push_back(indices[i]);
            }
        }
   //     Mesh* mesha = new Mesh();
        //std::cout<<"En esta Malla hay "<<mesh->mNumVertices<<" Vertices y "<<mesh->mNumFaces<<" Caras"<<std::endl;

    //  std::cout<<"Hay "<<mesh->mNumVertices<<" Vertices"std::endl;

      //  mesha->InitMesh(model);

         m_drawCount = model.indices.size();

        glGenVertexArrays(1,&m_vertexArrayObject);
        glBindVertexArray(m_vertexArrayObject);

        glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
        glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);//GL_STATIC_DRAW nunva se va a cambiar a la hora de dibujar

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
        glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);//GL_STATIC_DRAW nunva se va a cambiar a la hora de dibujar

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
        glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);//GL_STATIC_DRAW nunva se va a cambiar a la hora de dibujar

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2,3, GL_FLOAT, GL_FALSE, 0, 0);


        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);//GL_STATIC_DRAW nunva se va a cambiar a la hora de dibujar




        glBindVertexArray(0);



    //    meshes.push_back(mesha);
}

Mesh::EntradaMalla::EntradaMalla(float alto, float ancho, float prof){

    float x, y,z;
    int numVertices;
    int numIndices;
    modeloIndexado model;

    x= ancho/2;
    y= alto/2;
    z= prof/2;

    numVertices = 8;
    numIndices = 36;


Vertex vertices[]{       Vertex(glm::vec3(-x  ,   -y    ,   -z), glm::vec2(1.0,1.0)), //0 abajo  Derecha
                         Vertex(glm::vec3(-x  ,   y     ,   -z), glm::vec2(1.0,0.0)),  //1 arriba Derecha
                         Vertex(glm::vec3(x   ,   y     ,   -z), glm::vec2(0.0,0.0)),  //2 arriba izquierda
                         Vertex(glm::vec3(x   ,   -y    ,   -z), glm::vec2(0.0,1.0)),  //3 abajo izquierda

                         Vertex(glm::vec3(-x  ,   -y    ,   z), glm::vec2(0.0,1.0)), //4 abajo  Derecha
                         Vertex(glm::vec3(-x  ,   y     ,   z), glm::vec2(0.0,0.0)), //5 arriba Derecha
                         Vertex(glm::vec3(x   ,   y     ,   z), glm::vec2(1.0,0.0)),  //6 arriba izquierda
                         Vertex(glm::vec3(x   ,   -y    ,   z), glm::vec2(1.0,1.0))   //7 abajo izquierda
/*LAS NORMALES DEL CUBO ESTAN MAL PUESTAS*/
    };

       unsigned int indices[] =
            {
                0,1,3,      1,2,3,  //Cara frontal
                5,1,0,      0,4,5,  //Cara derecha
                2,6,7,      7,3,2,  //Cara Izquierda
                7,5,4,      5,7,6,  //Cara Trasera
                1,5,6,      1,6,2,  //Cara Superior
                0,7,4,      0,3,7   //Cara Inferior
            };


        for(unsigned int i =0; i< numVertices; i++){
        model.positions.push_back(*vertices[i].getPos());
        model.texCoords.push_back(*vertices[i].getTexCoord());
        model.normals.push_back(*vertices[i].getNormal());

    }
    for(unsigned int i =0; i< numIndices; i++){
            model.indices.push_back(indices[i]);

    }
    model.CalcNormals();
    InitMesh(model);
}


void Mesh::EntradaMalla::InitMesh(const modeloIndexado& model){



    m_drawCount = model.indices.size();

    glGenVertexArrays(1,&m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);//GL_STATIC_DRAW nunva se va a cambiar a la hora de dibujar

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);//GL_STATIC_DRAW nunva se va a cambiar a la hora de dibujar

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);//GL_STATIC_DRAW nunva se va a cambiar a la hora de dibujar

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,3, GL_FLOAT, GL_FALSE, 0, 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);//GL_STATIC_DRAW nunva se va a cambiar a la hora de dibujar




    glBindVertexArray(0);

 }

void Mesh::EntradaMalla::Draw(){

  //  std::cout<<"Dibujando malla tiene "<< m_drawCount<<" indices "<<std::endl;

    glBindVertexArray(m_vertexArrayObject);
//        std::cout<<"Antes Draw elemnts"<<std::endl;

    glDrawElements(GL_TRIANGLES,m_drawCount, GL_UNSIGNED_INT,0);

    //std::cout<<"Vertices "<<m_drawCount<<std::endl;
    //glDrawArrays(GL_TRIANGLES, 0,m_drawCount);
  //  std::cout<<"Antes Bind"<<std::endl;

    glBindVertexArray(0);
  //  std::cout<<"Acabado"<<std::endl;

 //   std::cout<<"Sale"<<std::endl;

}
void Mesh::Draw(){
    for(int i=0; i< MallasLeidas.size(); i++){
        MallasLeidas[i]->Draw();
    }

}
/*
void Mesh::begingDraw(Shader* shad, glm::mat4 matCam){
  int pos = pila->size()-1;
    std::cout<<pos<<std::endl;

    shad->Update(pila->at(pos), matCam);
    this->Draw();
}
void Mesh::endDraw(){}

int Mesh::getTipo(){
    return tipo;
}
*/
