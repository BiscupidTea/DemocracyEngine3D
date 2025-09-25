#pragma once
#include <vector>
#include "../Tools/Export.h"
#include "Plane.h"
#include "../Entities/Entity3D.h"
#include "../Camera/Camera.h"
#include "../Mesh/BoundingBox.h"

using namespace DemoEngine_Entities;
using namespace DemoEngine_Camera;
using namespace DemoEngine_Geometry;

class EXPORT Scene
{
public:
    Scene();
    ~Scene();

    void AddEntity(Entity3D* entity);
    void Draw(Camera* camera);

private:
    std::vector<Entity3D*> entities;
};
