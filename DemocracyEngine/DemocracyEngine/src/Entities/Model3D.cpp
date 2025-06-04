//#include "Model3D.h"
//#include <assimp/Importer.hpp>
//#include <assimp/postprocess.h>
//#include <stb_image.h>
//#include <iostream>
//
//unsigned int TextureFromFile(const char* path, const std::string& directory);
//
//Model3D::Model3D(const std::string& path) {
//    loadModel(path);
//}
//
//void Model3D::Draw(unsigned int shaderProgram) {
//    for (auto& mesh : meshes)
//        mesh.Draw(shaderProgram);
//}
//
//void Model3D::loadModel(const std::string& path) {
//    Assimp::Importer importer;
//    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
//
//    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
//        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << "\n";
//        return;
//    }
//
//    directory = path.substr(0, path.find_last_of('/'));
//    processNode(scene->mRootNode, scene);
//}
//
//void Model3D::processNode(aiNode* node, const aiScene* scene) {
//    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
//        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//        meshes.push_back(processMesh(mesh, scene));
//    }
//
//    for (unsigned int i = 0; i < node->mNumChildren; ++i)
//        processNode(node->mChildren[i], scene);
//}
//
//Mesh Model3D::processMesh(aiMesh* mesh, const aiScene* scene) {
//    std::vector<Vertex> vertices;
//    std::vector<unsigned int> indices;
//    std::vector<Texture> textures;
//
//    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
//        Vertex vertex;
//        vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
//        vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
//        vertex.TexCoords = mesh->mTextureCoords[0] ?
//            glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) : glm::vec2(0.0f);
//
//        vertices.push_back(vertex);
//    }
//
//    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
//        for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; ++j)
//            indices.push_back(mesh->mFaces[i].mIndices[j]);
//    }
//
//    if (mesh->mMaterialIndex >= 0) {
//        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
//        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//
//        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//    }
//
//    return Mesh(vertices, indices, textures);
//}
//
//std::vector<Texture> Model3D::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
//    std::vector<Texture> textures;
//
//    for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i) {
//        aiString str;
//        mat->GetTexture(type, i, &str);
//        std::string filename = str.C_Str();
//        filename = directory + "/" + filename;
//
//        bool skip = false;
//        for (auto& t : textures_loaded) {
//            if (t.path == filename) {
//                textures.push_back(t);
//                skip = true;
//                break;
//            }
//        }
//
//        if (!skip) {
//            Texture texture;
//            texture.id = TextureFromFile(filename.c_str(), directory);
//            texture.type = typeName;
//            texture.path = filename;
//            textures.push_back(texture);
//            textures_loaded.push_back(texture);
//        }
//    }
//
//    return textures;
//}
