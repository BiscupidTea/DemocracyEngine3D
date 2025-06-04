#include "Importer3D.h"
#include <iostream>

using namespace DemoEngine_Mesh;

void Importer3D::ImportModel(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate |
        aiProcess_FlipUVs |
        aiProcess_CalcTangentSpace |
        aiProcess_GenSmoothNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "Assimp import error: " << importer.GetErrorString() << std::endl;
        return;
    }

    std::cout << "Model loaded successfully: " << path << std::endl;
    ProcessNode(scene->mRootNode, scene);
}

void Importer3D::ProcessNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

void Importer3D::ProcessMesh(aiMesh* mesh)
{
    std::cout << "Mesh: " << mesh->mName.C_Str() << std::endl;
    std::cout << " - Vertices: " << mesh->mNumVertices << std::endl;
    std::cout << " - Faces: " << mesh->mNumFaces << std::endl;
}