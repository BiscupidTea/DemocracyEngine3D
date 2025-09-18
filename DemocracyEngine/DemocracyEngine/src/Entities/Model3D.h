#pragma once
#include "Entity3D.h"
#include "../Mesh/Importer3D.h"
#include "../Mesh/BoundingBox.h"

using namespace DemoEngine_Importer;
using namespace DemoEngine_Geometry;

namespace DemoEngine_Entities
{
    class EXPORT Model3D : public Entity3D
    {
    public:
        Model3D(vec3 newPosition = vec3(0.0f), vec3 newRotation = vec3(0.0f), vec3 newScale = vec3(1.0f));
        Model3D(vec3 newPosition, vec3 newRotation, vec3 newScale, const char* path, bool invertTexture);
        ~Model3D();
        void Draw() override;
        void AddTexture(std::string type, std::string path, bool invertTexture, bool ClearTexture);
        
        void SetShowModelWireframe(bool show);

        void DrawWireframes(const vec4& modelColor = vec4(0.0f, 1.0f, 0.0f, 1.0f), const vec4& meshesColor = vec4(1.0f, 0.0f, 1.0f, 1.0f)) const;
        const BoundingBox& GetLocalBoundingBox() const;
        BoundingBox GetWorldAABB() const;

    private:
        void AddMesh(const BasicMesh& mesh);

        std::vector<std::vector<Vertex>> vertices;
        std::vector<std::vector<unsigned int>> indices;

        std::vector<unsigned int> vaos;
        std::vector<unsigned int> vbos;
        std::vector<unsigned int> ebos;

        std::vector<Transform*> meshTransforms;
        std::vector<std::vector<Texture>> textures;

        BoundingBox m_boundingBox;
        std::vector<BoundingBox> m_meshBoundingBoxes;

        bool m_showModelWireframe = false;
    };
}
