#include "Model3D.h"

namespace DemoEngine_Entities
{
    Model3D::Model3D(vec3 newPosition, vec3 newRotation, vec3 newScale)
        : Entity3D(newPosition, newRotation, newScale)
    {
    }

    Model3D::Model3D(vec3 newPosition, vec3 newRotation, vec3 newScale, const char* path, bool invertTexture = false)
        : Entity3D(newPosition, newRotation, newScale)
    {
        auto importedData = Importer3D::ImportModel(path, invertTexture, this->transform);

        for (const auto& mesh : importedData.meshes)
        {
            AddMesh(mesh);
        }
    }

    Model3D::~Model3D()
    {
        for (size_t i = 0; i < vaos.size(); ++i)
        {
            glDeleteVertexArrays(1, &vaos[i]);
            glDeleteBuffers(1, &vbos[i]);
            glDeleteBuffers(1, &ebos[i]);
        }
        std::cout << "Destroy model3d" << std::endl;
    }

    void Model3D::Draw()
    {
        const auto& frustum = Renderer::GetRender()->MainCamera->GetFrustum();
        
        BoundingBox modelWorldAABB = GetWorldAABB();
        if (!frustum.IsBoxVisible(modelWorldAABB))
        {
            return;
        }
        
        for (size_t i = 0; i < vaos.size(); ++i)
        {
            BoundingBox meshWorldAABB = m_meshBoundingBoxes[i].Transform(meshTransforms[i]->GetModelWorldMatrix());
            if (frustum.IsBoxVisible(meshWorldAABB))
            {
                Renderer::GetRender()->DrawModel(
                    vaos[i],
                    static_cast<int>(indices[i].size()),
                    GetColor(),
                    meshTransforms[i]->GetModelWorldMatrix(),
                    textures[i],
                    material);
            }
        }
    }

    const BoundingBox& Model3D::GetLocalBoundingBox() const
    {
        return m_boundingBox;
    }

    BoundingBox Model3D::GetWorldAABB() const
    {
        BoundingBox worldAABB;
        if (m_meshBoundingBoxes.empty()) return worldAABB;
        
        for (size_t i = 0; i < m_meshBoundingBoxes.size(); ++i)
        {
            BoundingBox meshWorldAABB = m_meshBoundingBoxes[i].Transform(meshTransforms[i]->GetModelWorldMatrix());
            worldAABB.Expand(meshWorldAABB);
        }
        return worldAABB;
    }

    void Model3D::SetShowModelWireframe(bool show)
    {
        m_showModelWireframe = show;
    }

    void Model3D::SetShowMeshesWireframe(bool show)
    {
        m_showMeshesWireframe = show;
    }

    void Model3D::DrawWireframes(const vec4& modelColor, const vec4& meshesColor) const
    {
        const auto& frustum = Renderer::GetRender()->MainCamera->GetFrustum();
        const vec4 culledColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);

        if (m_showModelWireframe)
        {
            BoundingBox worldAABB = GetWorldAABB();
            bool isVisible = frustum.IsBoxVisible(worldAABB);
            Renderer::GetRender()->DrawWireBox(worldAABB, mat4(1.0f), isVisible ? modelColor : culledColor);
        }
        
        if (m_showMeshesWireframe)
        {
            for (size_t i = 0; i < m_meshBoundingBoxes.size(); ++i)
            {
                BoundingBox meshWorldAABB = m_meshBoundingBoxes[i].Transform(meshTransforms[i]->GetModelWorldMatrix());
                bool isVisible = frustum.IsBoxVisible(meshWorldAABB);
                Renderer::GetRender()->DrawWireBox(meshWorldAABB, mat4(1.0f), isVisible ? meshesColor : culledColor);
            }
        }
    }

    void Model3D::AddTexture(std::string type, std::string path, bool invertTexture, bool ClearTexture)
    {
        Texture tex;
        tex.id = Importer3D::LoadTextureFromFile(path.c_str(), invertTexture);
        tex.path = path;
        tex.type = type;

        for (int i = 0; i < textures.size(); ++i)
        {
            if (ClearTexture)
            {
                textures[i].clear();
            }
            textures[i].push_back(tex);
        }
    }

    void Model3D::AddMesh(const BasicMesh& mesh)
    {
        vertices.push_back(mesh.vertices);
        indices.push_back(mesh.indices);
        meshTransforms.push_back(mesh.transform);
        textures.push_back(mesh.textures);
        
        BoundingBox meshBBox;
        for (const auto& vertex : mesh.vertices)
        {
            meshBBox.Expand(vertex.position);
        }
        m_meshBoundingBoxes.push_back(meshBBox);
        
        mat4 relativeTransform(1.0f);
        Transform* current = mesh.transform;

        while (current && current != this->transform)
        {
            relativeTransform = current->GetModelLocalMatrix() * relativeTransform;
            current = current->GetParent();
        }

        for (const auto& vertex : mesh.vertices)
        {
            vec3 modelSpacePos = vec3(relativeTransform * vec4(vertex.position, 1.0f));
            m_boundingBox.Expand(modelSpacePos);
        }

        unsigned int vao, vbo, ebo;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], GL_STATIC_DRAW);

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
}
