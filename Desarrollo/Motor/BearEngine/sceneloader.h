 #ifndef SCENELOADER_H
#define SCENELOADER_H
#include <iostream>
#include <glm/glm.hpp>
#include "mesh.h"
#include <vector>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>



class sceneLoader
{
    public:
        sceneLoader(const char* filename);
        virtual ~sceneLoader();
        void draw();
        std::vector<Mesh*> getMeshes();

        std::vector<unsigned int> indices;

    protected:

    private:
        std::vector<Mesh*> meshes;
        void recursiveProcess(aiNode* node, const aiScene* scene);
        void processMesh(aiMesh* mesh, const aiScene* scebe);


};

#endif // SCENELOADER_H
