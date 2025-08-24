#pragma once
#include <vector>
#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "glew.h"
#include <../src/Tools/stb_image.h>

#include "../Tools/Export.h"

// Forward declaration
namespace DemoEngine_Entities { class Transform; }

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

    struct Texture
    {
        unsigned int id;
        std::string type;
        std::string path;
    };

    struct BasicMesh
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        DemoEngine_Entities::Transform* transform;

        BasicMesh(std::vector<Vertex> v, std::vector<unsigned int> i, std::vector<Texture> t, DemoEngine_Entities::Transform* tr)
            : vertices(std::move(v)), indices(std::move(i)), textures(std::move(t)), transform(tr) {}
    };

    struct ImportedModelData
    {
        std::string name;
        std::vector<BasicMesh> meshes;
    };

    static class EXPORT Importer3D
    {
    public:
        static ImportedModelData ImportModel(const std::string& path, bool invertTexture, DemoEngine_Entities::Transform* rootTransform);
        static unsigned int LoadTextureFromFile(const char* path, bool invertTexture);
    private:
        static void ProcessNode(aiNode* node, DemoEngine_Entities::Transform* parentTransform, const aiScene* scene, std::vector<BasicMesh>& outMeshes, const std::string& directory, bool invertTexture);
        static BasicMesh ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory, bool invertTexture, DemoEngine_Entities::Transform* transform);
        static std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName, const std::string& directory, bool invertTexture);
        static std::vector<Texture> m_loadedTexturesCache;
    };
}
