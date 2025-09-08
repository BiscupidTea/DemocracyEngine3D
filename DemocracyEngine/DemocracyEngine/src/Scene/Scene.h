#pragma once
#include <vector>

#include "../Entities/Entity3D.h"
#include "../Tools/Export.h"

using namespace DemoEngine_Camera;

class EXPORT Scene
{
public:
    Scene();
    ~Scene();

    void AddStaticEntity(Entity* entity);
    void AddDynamicEntity(Entity* entity);

    void Draw();

private:
    std::vector<Entity*> staticEntities;
    std::vector<Entity*> dynamicEntities;
};
