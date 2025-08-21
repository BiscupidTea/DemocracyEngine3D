#pragma once
#include "../Tools/Export.h"

#include <list>
#include <string>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <../src/Entities/Entity.h>

namespace DemoEngine_Entities
{
    class EXPORT Transform
    {
    public:
        explicit Transform(Entity* newEntity);
        Transform(Entity* newEntity, Transform* parent);
        Transform(Entity* newEntity, vec3 pos, vec3 rot, vec3 scale);
        ~Transform();
        std::string name;

        //Info
        vec3 GetGlobalPosition();
        vec3 GetLocalPosition();
        void SetPosition(vec3 newPosition);
        void SetLocalPosition(vec3 newPosition);
        
        void Translate(vec3 dir);

        vec3 getRotation();
        void SetLocalRotation(vec3 angle);
        void SetRotationX(float angle);
        void SetRotationY(float angle);
        void SetRotationZ(float angle);

        vec3 GetLocalScale();
        void SetLocalScale(vec3 newScale);

        void UpdateMatrix();

        //Family
        Transform* parent;
        std::vector<Transform*> child;
        void AddChild(Transform* model);
        
        //Global
        mat4x4 modelWorld;
        mat4x4 modelLocal;
        vec3 globalPosition;
        vec3 globalRotation;
        vec3 globalScale;

        //Local
        mat4 tranlateMatrix;
        mat4 rotationMatrix;
        mat4 scaleMatrix;

        vec3 localPosition;
        vec3 localRotation;
        vec3 localScale;

    protected:
    };
}
