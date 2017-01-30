#ifndef MODELOINDEXADO_H
#define MODELOINDEXADO_H

#include"glm/glm.hpp"
#include<iostream>
#include<vector>
class modeloIndexado
{

    public:
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    void CalcNormals();
    protected:

    private:
};

#endif // MODELOINDEXADO_H
