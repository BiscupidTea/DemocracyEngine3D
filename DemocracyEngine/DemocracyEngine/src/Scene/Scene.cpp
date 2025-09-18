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
    float camDist = plane.getSignedDistanceToPoint(cameraPos);

    if (camDist > 0.0f)
    {
        return box.IsOnOrBehindPlane(plane);
    }
    else if (camDist < 0.0f)
    {
        Plane flippedPlane(-plane.normal, -plane.distance);
        return box.IsOnOrBehindPlane(flippedPlane);
    }

    return false;
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

        entity->Draw();
    }
}
