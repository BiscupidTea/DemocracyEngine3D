#include "Transform.h"

using namespace DemoEngine_Entities;

Transform::Transform(Entity* newEntity)
{
    modelWorld = glm::mat4(1.0f);
    tranlateMatrix = glm::mat4(1.0f);
    scaleMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::mat4(1.0f);
    glm::vec3 newPos(0, 0, 0);
    localPosition = {newPos.x, newPos.y, newPos.z};
    tranlateMatrix = glm::translate(tranlateMatrix, newPos);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));

    UpdateMatrix();
    SetLocalPosition(localPosition);
}

Transform::Transform(Entity* newEntity, Transform* parent)
{
    modelWorld = glm::mat4(1.0f);
    tranlateMatrix = glm::mat4(1.0f);
    scaleMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::mat4(1.0f);
    glm::vec3 newPos(0, 0, 0);
    localPosition = {newPos.x, newPos.y, newPos.z};
    tranlateMatrix = glm::translate(tranlateMatrix, newPos);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));

    if (parent != nullptr)
    {
        this->parent = parent;
        parent->child.push_back(this);
    }
    UpdateMatrix();
    SetLocalPosition(localPosition);
}

Transform::Transform(Entity* newEntity, vec3 pos, vec3 rot, vec3 scale)
{
    modelWorld = glm::mat4(1.0f);
    tranlateMatrix = glm::mat4(1.0f);
    scaleMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::mat4(1.0f);
    localPosition = pos;
    localRotation = glm::vec3(0);
    localScale = scale;
    SetRotationX(rot.x);
    SetRotationY(rot.y);
    SetRotationZ(rot.z);
    UpdateMatrix();
}
