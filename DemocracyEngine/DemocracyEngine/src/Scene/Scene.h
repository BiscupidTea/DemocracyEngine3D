#pragma once
#include <vector>

#include "../Tools/Export.h"
#include "Plane.h"
#include "../Entities/Entity3D.h"
#include "../Camera/Camera.h"

using namespace DemoEngine_Entities;
using namespace DemoEngine_Camera;

class EXPORT Scene
{
public:
    Scene();
    ~Scene();

    void AddEntity(Entity3D* entity);
    void AddPlane(const Plane& plane);

    void Draw(Camera* camera);

private:
    std::vector<Entity3D*> entities;
    std::vector<Plane> bspPlanes;
};
