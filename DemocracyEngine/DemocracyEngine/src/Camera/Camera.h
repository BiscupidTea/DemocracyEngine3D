#pragma once
#include "../Tools/Export.h"
#include "../Input/Input.h"

#include "../Entities/Entity.h"

using namespace glm;
using namespace DemoEngine_Entities;
using namespace DemoEngine_Input;

enum class CameraMode { FirstPerson, ThirdPerson };

class EXPORT Camera : public Entity
{
private:
    Input* input = nullptr;

    mat4x4 proyection;
    mat4x4 view;

    vec3 LocalPosition;
    vec3 cameraFront;
    vec3 cameraUp;

    CameraMode mode;

    vec3 thirdPersonTarget = vec3(0.0f);
    bool ThirdPersonCamera = false;
    float thirdPersonDistance = 500.0f;
    float thirdPersonHeight = 250.0f;

    float yaw = -90.0f;
    float pitch = 0.0f;
    float mouseSensitivity = 0.1f;
    float cameraSpeed = 15.0f;

public:
    Camera(vec2 aspect, float maxDistance, vec3 newPosition, vec3 newRotation, vec3 newScale, CameraMode cameraMode);

    void Update();

    vec3 GetCameraPosition();
    vec3 GetCameraFoward();
    vec3 GetCameraRight();
    mat4x4 GetCameraProyection();
    mat4x4 GetCameraView();

    void SetCameraPosition(vec3 NewPosition);
    void TranslateCamera(vec3 dir);
    void RotateCamera(vec3 newRotation);

    void SetCameraMode(CameraMode newMode);
    void SetCameraTarget(vec3 newTarget);

    void SetInput(Input* newInput);
};
