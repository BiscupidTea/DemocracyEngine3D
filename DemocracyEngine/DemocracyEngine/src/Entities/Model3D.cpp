#include "Model3D.h"

namespace DemoEngine_Entities
{
    Model3D::Model3D(vec3 newPosition, vec3 newRotation, vec3 newScale, const char* path)
        : Entity3D(newPosition, newRotation, newScale)
    {
        auto data = Importer3D::ImportModel(path);

        const std::vector<std::vector<Vertex>>& vertices = std::get<0>(data);
        const std::vector<std::vector<unsigned int>>& indices = std::get<1>(data);

        for (size_t i = 0; i < vertices.size(); ++i)
            AddMesh(vertices[i], indices[i]);
    }

    Model3D::~Model3D()
    {
       cout << "Destroy model3d" << endl; 
    }

    void Model3D::Draw()
    {
        UpdateTMatrix();

        for (size_t i = 0; i < vaos.size(); ++i)
        {
            Renderer::GetRender()->DrawEntity3D(
                vaos[i],
                static_cast<int>(indices[i].size()),
                getColor(),
                model,
                textureID,
                material
            );
        }
    }

    void Model3D::AddMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    {
        this->vertices.push_back(vertices);
        this->indices.push_back(indices);

        unsigned int vao, vbo, ebo;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
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
