#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
    for (Entity* entity : staticEntities)
    {
        delete entity;
    }
    for (Entity* entity : dynamicEntities)
    {
        delete entity;
    }
}

void Scene::AddStaticEntity(Entity* entity)
{
    staticEntities.push_back(entity);
}

void Scene::AddDynamicEntity(Entity* entity)
{
    dynamicEntities.push_back(entity);
}

void Scene::Draw()
{
    for (Entity* entity : staticEntities)
    {
        if (entity->IsActive())
        {
            entity->Draw();
        }
    }

    for (Entity* entity : dynamicEntities)
    {
        if (entity->IsActive())
        {
            entity->Draw();
        }
    }
}
