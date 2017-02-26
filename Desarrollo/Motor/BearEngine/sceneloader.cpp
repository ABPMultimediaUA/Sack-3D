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

    std::cout<< "El modelo esta compuesto por "<<scene->mRootNode->mNumChildren<<" Mallas"<<std::endl;

      //  std::cout<< "modelo cargado con exito "<< filename<<std::endl;

    recursiveProcess(scene->mRootNode, scene );

}

sceneLoader::~sceneLoader()
{
    for(int i =0; i< meshes.size();i++)
        delete meshes[i];
}


std::vector<Mesh*> sceneLoader::getMeshes(){
    return meshes;
}
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
/*
    for(unsigned int i =0; i< numVertices; i++){
        model.positions.push_back(*vertices[i].getPos());
        model.texCoords.push_back(*vertices[i].getTexCoord());
        model.normals.push_back(*vertices[i].getNormal());

    }
    for(unsigned int i =0; i< numIndices; i++){
            model.indices.push_back(indices[i]);

    }
    InitMesh(model);

*/
    for(int i=0;i<mesh->mNumVertices;i++){


    glm::vec3 position;
    glm::vec2 uV;
    glm::vec3 normal;

   // (glm::vec3(mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z)
   // (mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y
     position.x= mesh->mVertices[i].x;
     position.y= mesh->mVertices[i].y;
     position.z= mesh->mVertices[i].z;
         model.positions.push_back(position);
  //if(mesh->HasTextureCoords()){

    uV.x=0;
    uV.y=0;
  //  uV.x= mesh->mTextureCoords[0][i].x;
   // uV.y= mesh->mTextureCoords[0][i].y;
     model.texCoords.push_back(uV);
  //}
 if(mesh->HasNormals()){


    normal.x  = mesh->mNormals[i].x;
    normal.y  = mesh->mNormals[i].y;
    normal.z  = mesh->mNormals[i].z;
    model.normals.push_back(normal);
 }else{
    model.CalcNormals();
    model.normals.push_back(normal);
 }

/*
    if(mesh->HasNormals()){

    }else{

    }*/


   //

    //Vertex vertice ((glm::vec3(mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z)),glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y),glm::vec3(glm::vec3(mesh->mNormals[i].x,mesh->mNormals[i].y,mesh->mNormals[i].z)));
   // Vertex(glm::vec3(-0.5,-0.5,-0.5), glm::vec2(1.0,1.0), glm::vec3(-1,-1,-1));
   // vertices.push_back(vertice);


    }
    for(int i =0; i<mesh->mNumFaces;i++){
        aiFace  face=mesh->mFaces[i];
        for(int j=0;j<face.mNumIndices;j++){ // 0..2
            model.indices.push_back(face.mIndices[j]);
         //   model.indices.push_back(indices[i]);
        }
    }
 /*   aiMaterial* mat= mMaterials[mesh->mMaterialIndex];
    for(int i=0;i<mat->GetTextureCount(aiTextureType_DIFFUSE);i++){
        aiString str;
        mat->GetTexture(aiTextureType_DIFFUSE,i,&str);
        textureData tmp;
        tmp.id=loadTexture(str.C_Str());
        tmp.type=0;
        textures.push_back(tmp);
    }*/
    Mesh* mesha = new Mesh();
    std::cout<<"En esta Malla"<<std::endl;
    std::cout<<"Hay "<<mesh->mNumVertices<<" Vertices"<<std::endl;
    std::cout<<"Hay "<<mesh->mNumFaces<<" Caras"<<std::endl;
 //   std::cout<<"Hay "<<mesh->mNumVertices<<" Vertices"std::endl;

    mesha->InitMesh(model);
    meshes.push_back(mesha);
}

void sceneLoader::draw(){
    for(int i =0; i<meshes.size();i++)
        meshes[i]->Draw();
}


