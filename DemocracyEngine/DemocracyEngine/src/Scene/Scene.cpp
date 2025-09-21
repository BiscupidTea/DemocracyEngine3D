#include "Scene.h"

#include "../Entities/Model3D.h"

Scene::Scene()
{
}

Scene::~Scene()
{
    for (Entity3D* entity : entities)
    {
        delete entity;
    }
}

void Scene::AddEntity(Entity3D* entity)
{
    entities.push_back(entity);
}

void Scene::AddPlane(const Plane& plane)
{
    bspPlanes.push_back(plane);
}

bool Scene::EntityIsVisibleBSP(Entity3D* entity, const std::vector<Plane>& bspPlanes, const std::vector<bool>& cameraSides)
{
    BoundingBox box;
    Model3D* model = dynamic_cast<Model3D*>(entity);
    if (model)
        box = model->ComputeBoundingBoxRecursive(model->transform);
    else
        box = BoundingBox(entity->transform->GetGlobalPosition(), entity->transform->GetGlobalPosition()); // punto

    glm::vec3 corners[8];
    box.GetCorners(corners);

    for (size_t i = 0; i < bspPlanes.size(); ++i)
    {
        bool anyCornerOnCameraSide = false;
        for (int c = 0; c < 8; ++c)
        {
            if (bspPlanes[i].getSide(corners[c]) == cameraSides[i])
            {
                anyCornerOnCameraSide = true;
                break;
            }
        }
        if (!anyCornerOnCameraSide)
            return false;
    }

    return true;
}

void Scene::Draw(Camera* camera)
{
    if (!camera) return;

    std::vector<bool> cameraSides;
    for (const Plane& plane : bspPlanes)
        cameraSides.push_back(plane.getSide(camera->GetCameraPosition()));

    for (Entity3D* entity : entities)
    {
        if (!entity->IsActive())
            continue;

        if (EntityIsVisibleBSP(entity, bspPlanes, cameraSides))
            entity->Draw();
    }
}
