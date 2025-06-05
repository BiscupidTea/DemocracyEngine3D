#include "Importer3D.h"

namespace DemoEngine_Importer
{
    std::tuple<
        std::vector<std::vector<Vertex>>,
        std::vector<std::vector<unsigned int>>,
        std::vector<unsigned int>
    > Importer3D::ImportModel(const std::string& path)
    {
        std::vector<std::vector<Vertex>> allVertices;
        std::vector<std::vector<unsigned int>> allIndices;
        std::vector<unsigned int> allTextures;

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path,
            aiProcess_Triangulate |
            aiProcess_FlipUVs |
            aiProcess_CalcTangentSpace |
            aiProcess_PreTransformVertices);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return { allVertices, allIndices, allTextures };
        }

        std::string directory = path.substr(0, path.find_last_of('/'));

        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[i];
            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;

            for (unsigned int v = 0; v < mesh->mNumVertices; v++)
            {
                Vertex vertex;
                vertex.position = glm::vec3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);
                vertex.normal = mesh->HasNormals() ? glm::vec3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z) : glm::vec3(0.0f);
                vertex.texCoords = mesh->mTextureCoords[0] ? glm::vec2(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y) : glm::vec2(0.0f);
                vertex.tangent = mesh->HasTangentsAndBitangents() ? glm::vec3(mesh->mTangents[v].x, mesh->mTangents[v].y, mesh->mTangents[v].z) : glm::vec3(0.0f);
                vertex.bitangent = mesh->HasTangentsAndBitangents() ? glm::vec3(mesh->mBitangents[v].x, mesh->mBitangents[v].y, mesh->mBitangents[v].z) : glm::vec3(0.0f);
                vertices.push_back(vertex);
            }

            for (unsigned int f = 0; f < mesh->mNumFaces; f++)
            {
                aiFace face = mesh->mFaces[f];
                for (unsigned int j = 0; j < face.mNumIndices; j++)
                    indices.push_back(face.mIndices[j]);
            }

            unsigned int textureID = 0;
            if (mesh->mMaterialIndex >= 0)
            {
                aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
                if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
                {
                    aiString str;
                    material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
                    std::string fullPath = directory + "/" + str.C_Str();

                    //textureID = LoadTextureFromFile(fullPath.c_str());
                }
            }

            allVertices.push_back(vertices);
            allIndices.push_back(indices);
            allTextures.push_back(textureID);
        }

        return { allVertices, allIndices, allTextures };
    }
}
