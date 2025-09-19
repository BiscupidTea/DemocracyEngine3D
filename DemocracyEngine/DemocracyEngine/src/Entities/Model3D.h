#pragma once
#include "Entity3D.h"
#include "../Mesh/BasicMesh.h"
#include "../Mesh/BoundingBox.h"

namespace DemoEngine_Entities
{
    class EXPORT Model3D : public Entity3D
    {
    public:
        Model3D(vec3 newPosition = vec3(0.0f), vec3 newRotation = vec3(0.0f), vec3 newScale = vec3(1.0f));
        Model3D(vec3 newPosition, vec3 newRotation, vec3 newScale, const char* path, bool invertTexture = false);
        Model3D(const BasicMesh& mesh);
        ~Model3D();

        void Draw() override;
        BoundingBox ComputeBoundingBoxRecursive(Transform* node);
        void AddTexture(std::string type, std::string path, bool invertTexture = false, bool clearTexture = false);

        BoundingBox GetBoundingBox() const;

        bool drawWireframe = true;

    private:
        void AddMesh(const BasicMesh& mesh);

        std::vector<std::vector<Vertex>> vertices;
        std::vector<std::vector<unsigned int>> indices;

        std::vector<unsigned int> vaos;
        std::vector<unsigned int> vbos;
        std::vector<unsigned int> ebos;

        std::vector<Transform*> meshTransforms;
        std::vector<std::vector<Texture>> textures;

        std::vector<BoundingBox> meshBoundingBoxes;
    };
}
