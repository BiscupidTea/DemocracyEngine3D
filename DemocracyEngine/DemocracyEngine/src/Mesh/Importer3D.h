#pragma once

#include <string>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace DemoEngine_Mesh
{
    class Importer3D
    {
    public:
        void ImportModel(const std::string& path);

    private:
        void ProcessNode(aiNode* node, const aiScene* scene);
        void ProcessMesh(aiMesh* mesh);
    };
}