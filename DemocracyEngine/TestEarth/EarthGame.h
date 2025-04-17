#include "BaseGame/BaseGame.h"
#include "Entities/Sprite.h"
#include "CollisionManager/CollisionManager.h"
#include "Entities/Cube.h"
#include "Entities/Square.h"
#include "Entities/Triangle.h"
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

    Cube* cube;
    Triangle* triangle;
    Square* square;

    Sprite* player;
    Sprite* floor;
    Sprite* pingu1;
    Sprite* pingu2;
    DemoTimer* timer;

    float playerSpeed;

public:
    EarthGame();
    ~EarthGame();

    void Init() override;
    void Update() override;
    void DeInit() override;
};
