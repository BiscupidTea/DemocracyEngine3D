#include "Scene.h"

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

bool Scene::IsOccludedByPlane(const Plane& plane, const BoundingBox& box, const glm::vec3& cameraPos)
{
    glm::vec3 boxCenter = box.GetCenter();

    float camDist = plane.getSignedDistanceToPoint(cameraPos);
    float boxDist = plane.getSignedDistanceToPoint(boxCenter);
    
    return (camDist > 0.0f && boxDist < 0.0f) || (camDist < 0.0f && boxDist > 0.0f);
}

void Scene::Draw(Camera* camera)
{
    if (!camera) return;

    const auto& frustum = camera->GetFrustum();
    const glm::vec3 cameraPos = camera->GetCameraPosition();

    for (Entity3D* entity : entities)
    {
        if (!entity->IsActive())
            continue;

        BoundingBox worldAABB = entity->GetWorldAABB();

        if (!frustum.IsBoxVisible(worldAABB))
            continue;

        bool isOccluded = false;
        for (const Plane& occluderPlane : bspPlanes)
        {
            if (IsOccludedByPlane(occluderPlane, worldAABB, cameraPos))
            {
                isOccluded = true;
                break;
            }
        }

        if (!isOccluded)
            entity->Draw();
    }
}
