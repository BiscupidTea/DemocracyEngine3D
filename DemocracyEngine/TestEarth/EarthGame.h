#pragma once
#include "BaseGame/BaseGame.h"
#include "Entities/Model3D.h"
#include "Entities/Cube.h"
#include "Scene/Scene.h"

using namespace DemoEngine_BaseGame;
using namespace DemoEngine_Entities;

class EarthGame final : public BaseGame
{
private:
    vec3 PlayerPosition;
    vec3 PlayerScale;
    vec3 PlayerRotation;
    vec4 PlayerColor;

    float cameraRotation;
    Scene* testScene = nullptr;

    Model3D* SnowCat = nullptr;
    Model3D* Tank = nullptr;
    Transform* tankTurretTransform = nullptr;
    Transform* tankLeftCannonTransform = nullptr;
    Transform* tankRightCannonTransform = nullptr;

    float playerSpeed;

public:
    EarthGame();
    ~EarthGame();

    void Init() override;
    void Update() override;
    void DeInit() override;
};
