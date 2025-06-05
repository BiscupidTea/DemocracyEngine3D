#pragma once
#include <vector>
#include <string>

#include <glm/ext/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>


namespace DemoEngine_Importer
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
        glm::vec3 tangent;
        glm::vec3 bitangent;
    };

    class Importer3D
    {
    public:
        static std::tuple<
            std::vector<std::vector<Vertex>>,         
            std::vector<std::vector<unsigned int>>,   
            std::vector<unsigned int>                 
        > ImportModel(const std::string& path);
    };

    unsigned int LoadTextureFromFile(const char* path);
}