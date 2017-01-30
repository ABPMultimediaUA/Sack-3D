#include "sceneloader.h"

sceneLoader::sceneLoader(const char* filename)
{


    const aiScene* scene = aiImportFile(filename,
                              aiProcess_GenSmoothNormals    |   aiProcess_Triangulate |
                              aiProcess_CalcTangentSpace    |   aiProcess_FlipUVs);


    if(scene->mFlags){
        std::cout<< "Ha habido un error al cargar el modelo "<< filename<<std::endl;
        return;
    }

    std::cout<< "El modelo esta compuesto por "<< scene->mRootNode->mNumChildren<<" Mallas"<<std::endl;


    recursiveProcess(scene->mRootNode, scene );

}

sceneLoader::~sceneLoader()
{
      for(int i =0; i< meshes.size();i++)
        delete meshes[i];
}


std::vector<Mesh*>& getMeshes();
void sceneLoader::recursiveProcess(aiNode* node, const aiScene* scene){
  if(node!=NULL){



    //Process
    for(int i =0; i<node->mNumMeshes;i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];


        processMesh(mesh,scene);
    }

    //recursion
    for(int i =0; i<node->mNumChildren;i++){

        recursiveProcess(node->mChildren[i],scene);
    }
  }
}
void sceneLoader::processMesh(aiMesh* mesh, const aiScene* scene){


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

    uV.x=0;
    uV.y=0;

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
         
        }
    }

    Mesh* mesha = new Mesh();
    std::cout<<"En esta Malla"<<std::endl;
    std::cout<<"Hay "<<mesh->mNumVertices<<" Vertices"<<std::endl;
    std::cout<<"Hay "<<mesh->mNumFaces<<" Caras"<<std::endl;
    mesha->InitMesh(model);
    meshes.push_back(mesha);
}

void sceneLoader::draw(){
    for(int i =0; i<meshes.size();i++)
        meshes[i]->Draw();
}


