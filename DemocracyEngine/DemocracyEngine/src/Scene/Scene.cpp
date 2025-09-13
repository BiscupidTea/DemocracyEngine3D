#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
    for (Entity* entity : entities)
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

void Scene::Draw(Camera* camera)
{
    if (!camera) return;

    const auto& frustum = camera->GetFrustum();
    const vec3 cameraPos = camera->GetCameraPosition();

    for (Entity3D* entity : entities)
    {
        if (!entity->IsActive())
        {
            continue;
        }
        
        BoundingBox worldAABB = entity->GetWorldAABB();
        if (!frustum.IsBoxVisible(worldAABB))
        {
            continue;
        }
        
        bool isOccluded = false;
        for (const Plane& occluderPlane : bspPlanes)
        {
            if (occluderPlane.getSignedDistanceToPoint(cameraPos) < 0)
            {
                continue;
            }
            
            if (worldAABB.IsOnOrBehindPlane(occluderPlane))
            {
                isOccluded = true;
                break;
            }
        }
        
        if (!isOccluded)
        {
            entity->Draw();
        }
    }
}
