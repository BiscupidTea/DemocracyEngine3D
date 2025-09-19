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

void Scene::Draw(Camera* camera)
{
    if (!camera) return;

    for (Entity3D* entity : entities)
    {
        if (!entity->IsActive())
            continue;

        entity->Draw();
    }
}
