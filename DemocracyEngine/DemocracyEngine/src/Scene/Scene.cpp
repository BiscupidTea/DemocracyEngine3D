#include "Scene.h"
#include <glm/glm.hpp>

#include "../Entities/Model3D.h"

Scene::Scene() {}

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

void Scene::Draw(Camera* camera)
{
    if (!camera) return;

    std::vector<bool> cameraSides;
    std::vector<Plane> bspPlanes = camera->GetBSPPlanes();
    for (const Plane& plane : bspPlanes)
        cameraSides.push_back(plane.getSide(camera->GetCameraPosition()));

    for (Entity3D* entity : entities)
    {
        Model3D* model = dynamic_cast<Model3D*>(entity);
        if (model)
        {
            model->DrawOccluded(bspPlanes, cameraSides);
        }
        else
        {
            entity->Draw();
        }
    }
}