#define GLM_ENABLE_EXPERIMENTAL

#include "Importer3D.h"
#include "../Entities/Transform.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace DemoEngine_Entities;

namespace DemoEngine_Importer
{
    std::vector<Texture> Importer3D::m_loadedTexturesCache;

    ImportedModelData Importer3D::ImportModel(const std::string& path, bool invertTexture, Transform* rootTransform)
    {
        ImportedModelData modelData;
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path,
            aiProcess_Triangulate |
            aiProcess_FlipUVs |
            aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return modelData;
        }
        
        aiNode* targetNode = scene->mRootNode;
        
        if (targetNode->mNumMeshes == 0 && targetNode->mNumChildren == 1)
        {
            aiNode* childNode = targetNode->mChildren[0];
            if (childNode->mNumMeshes > 0)
            {
                targetNode = childNode;
            }
        }
        
        std::string nodeName = targetNode->mName.C_Str();
        
        if (nodeName.empty() || nodeName == "rootnode" || nodeName == "RootNode" || nodeName.find("Assimp") != std::string::npos)
        {
            size_t lastSlash = path.find_last_of("/\\");
            lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
            size_t lastDot = path.rfind('.');
            if (lastDot == std::string::npos || lastDot < lastSlash)
            {
                 modelData.name = path.substr(lastSlash);
            }
            else
            {
                 modelData.name = path.substr(lastSlash, lastDot - lastSlash);
            }
        }
        else
        {
            modelData.name = nodeName;
            if (rootTransform) rootTransform->SetName(nodeName);
        }
        
        const std::string directory = path.substr(0, path.find_last_of('/'));
        std::cout << "Model loaded: " << path << " | Name: " << modelData.name << " | Meshes: " << scene->mNumMeshes << std::endl;
        
        if (rootTransform)
        {
            ProcessNode(targetNode, rootTransform, scene, modelData.meshes, directory, invertTexture);
        }

        return modelData;
    }

    void Importer3D::ProcessNode(aiNode* node, Transform* parentTransform, const aiScene* scene, std::vector<BasicMesh>& outMeshes, const std::string& directory, bool invertTexture)
    {
        Transform* currentTransform = parentTransform;
        
        if (node->mName.C_Str() != parentTransform->GetName())
        {
            currentTransform = new Transform(parentTransform->GetOwner());
            currentTransform->SetName(node->mName.C_Str());
            currentTransform->SetParent(parentTransform);
            
            const aiMatrix4x4& t = node->mTransformation;
            glm::mat4 localMat = glm::transpose(glm::make_mat4(&t.a1));

            vec3 scale, pos, skew;
            vec4 persp;
            quat rot;
            glm::decompose(localMat, scale, rot, pos, skew, persp);

            currentTransform->SetLocalPosition(pos);
            currentTransform->SetLocalRotation(glm::degrees(glm::eulerAngles(rot)));
            currentTransform->SetLocalScale(scale);
        }
        
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            outMeshes.push_back(ProcessMesh(mesh, scene, directory, invertTexture, currentTransform));
        }
        
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], currentTransform, scene, outMeshes, directory, invertTexture);
        }
    }

    BasicMesh Importer3D::ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory, bool invertTexture, Transform* transform)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            vertex.normal = mesh->HasNormals() ? glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z) : glm::vec3(0.0f);
            vertex.texCoords = mesh->mTextureCoords[0] ? glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) : glm::vec2(0.0f);
            vertex.tangent = mesh->HasTangentsAndBitangents() ? glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z) : glm::vec3(0.0f);
            vertex.bitangent = mesh->HasTangentsAndBitangents() ? glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z) : glm::vec3(0.0f);
            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            const aiFace& face = mesh->mFaces[i];
            indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
        }

        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", directory, invertTexture);
            std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", directory, invertTexture);
            std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal", directory, invertTexture);
            std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height", directory, invertTexture);
            std::vector<Texture> BaseColorMaps = LoadMaterialTextures(material, aiTextureType_BASE_COLOR, "texture_baseColor", directory, invertTexture);

            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
            textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
            textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
            textures.insert(textures.end(), BaseColorMaps.begin(), BaseColorMaps.end());
        }

        //std::cout << "Mesh loaded for transform '" << transform->GetName() << "': Vertices = " << vertices.size() << std::endl;
        return BasicMesh(std::move(vertices), std::move(indices), std::move(textures), transform);
    }

    std::vector<Texture> Importer3D::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName, const std::string& directory, bool invertTexture)
    {
        std::vector<Texture> textures;

        for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            
            // 1. Check if texture was loaded before
            bool skip = false;
            for(const auto& loadedTex : m_loadedTexturesCache)
            {
                if(std::strcmp(loadedTex.path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(loadedTex);
                    skip = true; // Texture found in cache, skip loading
                    break;
                }
            }

            if(skip)
            {
                continue;
            }

            // 2. If not loaded, load it now
            std::string texturePath = directory + "/" + str.C_Str();
            unsigned int textureID = LoadTextureFromFile(texturePath.c_str(), invertTexture);
            Texture texture;
            texture.id = textureID;
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            m_loadedTexturesCache.push_back(texture); // 3. Add to cache
        }
        return textures;
    }


    unsigned int Importer3D::LoadTextureFromFile(const char* path, bool invertTexture)
    {
        //std::cout << "Loading texture from: " << path << std::endl;

        stbi_set_flip_vertically_on_load(invertTexture);
        
        int width, height, nrComponents;
        unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
        if (!data)
        {
            std::cout << "Failed to load texture: " << path << std::endl;
            return 0;
        }

        GLenum format = (nrComponents == 1) ? GL_RED :
                        (nrComponents == 3) ? GL_RGB :
                        GL_RGBA;

        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        //std::cout << "Texture loaded OK: " << path << ", ID: " << textureID << std::endl;
        return textureID;
    }

}