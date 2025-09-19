#include "Model3D.h"
#include "../Render/Renderer.h"

#include <iostream>

using namespace DemoEngine_Entities;
using namespace DemoEngine_Importer;
using namespace DemoEngine_Geometry;

namespace DemoEngine_Entities
{
    Model3D::Model3D(vec3 newPosition, vec3 newRotation, vec3 newScale)
        : Entity3D(newPosition, newRotation, newScale)
    {
    }

    Model3D::Model3D(vec3 newPosition, vec3 newRotation, vec3 newScale, const char* path, bool invertTexture)
        : Entity3D(newPosition, newRotation, newScale)
    {
        ImportedModelData data = Importer3D::ImportModel(path, invertTexture, this->transform);
        for (const auto& mesh : data.meshes)
        {
            AddMesh(mesh);
        }
    }

    Model3D::Model3D(const BasicMesh& mesh)
        : Entity3D(vec3(0.0f), vec3(0.0f), vec3(1.0f))
    {
        AddMesh(mesh);
    }

    Model3D::~Model3D()
    {
        for (size_t i = 0; i < vaos.size(); ++i)
        {
            glDeleteVertexArrays(1, &vaos[i]);
            glDeleteBuffers(1, &vbos[i]);
            glDeleteBuffers(1, &ebos[i]);
        }
        std::cout << "Delete Model3D" << std::endl;
    }

    void Model3D::AddMesh(const BasicMesh& mesh)
    {
        vertices.push_back(mesh.vertices);
        indices.push_back(mesh.indices);
        meshTransforms.push_back(mesh.transform);
        textures.push_back(mesh.textures);

        BoundingBox box;
        for (auto& v : mesh.vertices)
            box.Expand(v.position);
        meshBoundingBoxes.push_back(box);

        unsigned int vao, vbo, ebo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
        glEnableVertexAttribArray(4);

        glBindVertexArray(0);

        vaos.push_back(vao);
        vbos.push_back(vbo);
        ebos.push_back(ebo);
    }

    void Model3D::Draw()
    {
        for (size_t i = 0; i < vaos.size(); ++i)
        {
            Renderer::GetRender()->DrawModel(
                vaos[i],
                static_cast<int>(indices[i].size()),
                GetColor(),
                meshTransforms[i]->GetModelWorldMatrix(),
                textures[i],
                material
            );

            if(drawWireframe && meshTransforms[i] == transform)
            {
                BoundingBox box = ComputeBoundingBoxRecursive(transform);
                Renderer::GetRender()->DrawWireBox(box, transform->GetModelWorldMatrix(), vec4(1,0,0,1));
            }
        }
    }

    BoundingBox Model3D::ComputeBoundingBoxRecursive(Transform* node)
    {
        BoundingBox box;
        for (size_t i = 0; i < meshTransforms.size(); ++i)
        {
            if (meshTransforms[i] == node)
                box.Expand(meshBoundingBoxes[i]);
        }

        for (Transform* child : node->GetChildren())
        {
            box.Expand(ComputeBoundingBoxRecursive(child));
        }

        return box;
    }

    void Model3D::AddTexture(std::string type, std::string path, bool invertTexture, bool clearTexture)
    {
        Texture tex;
        tex.id = Importer3D::LoadTextureFromFile(path.c_str(), invertTexture);
        tex.type = type;
        tex.path = path;

        for (size_t i = 0; i < textures.size(); ++i)
        {
            if(clearTexture) textures[i].clear();
            textures[i].push_back(tex);
        }
    }

    BoundingBox Model3D::GetBoundingBox() const
    {
        BoundingBox box;
        for (size_t i = 0; i < meshBoundingBoxes.size(); ++i)
        {
            box.Expand(meshBoundingBoxes[i].Transform(meshTransforms[i]->GetModelWorldMatrix()));
        }
        return box;
    }
}