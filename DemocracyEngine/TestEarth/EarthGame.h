#pragma once
#include "BaseGame/BaseGame.h"
#include "Entities/Sprite.h"
#include "Entities/Model3D.h"
#include "CollisionManager/CollisionManager.h"
#include "Entities/Cube.h"
#include "TileMap/TileMap.h"

using namespace DemoEngine_BaseGame;
using namespace DemoEngine_Entities;
using namespace DemoEngine_Collisions;
using namespace DemoEngine_TileMap;

class EarthGame final : public BaseGame
{
private:
    vec3 PlayerPosition;
    vec3 PlayerScale;
    vec3 PlayerRotation;
    vec4 PlayerColor;

    float cameraRotation;

    Animation* anim;

    Cube* player;
    Cube* cube;

    Cube* floor;
    Cube* wall1;
    Cube* wall2;
    Cube* wall3;
    Cube* wall4;
    Cube* Top;
    DemoTimer* timer;

    Model3D* yukinko;
    Model3D* backPack;
    Model3D* SnowCat;

    float playerSpeed;

public:
    EarthGame();
    ~EarthGame();

    void Init() override;
    void Update() override;
    void DeInit() override;
};
