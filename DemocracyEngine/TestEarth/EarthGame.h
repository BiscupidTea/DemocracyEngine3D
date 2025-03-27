#include "BaseGame/BaseGame.h"
#include "Entities/Sprite.h"
#include "CollisionManager/CollisionManager.h"
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

	Animation* anim;
	
	Sprite* player;
	DemoTimer* timer;

	int playerSpeed;

public:
	EarthGame();
	~EarthGame();

	void Init() override;
	void Update() override;
	void DeInit() override;
};