#include "BaseGame/BaseGame.h"
#include "Entities/Sprite.h"
#include "Entities/Triangle.h"
#include "Entities/Square.h"
#include "CollisionManager/CollisionManager.h"
#include "TileMap/TileMap.h"

using namespace DemoEngine_BaseGame;
using namespace DemoEngine_Entities;
using namespace DemoEngine_Collisions;

class EarthGame final : public BaseGame
{
private:
	vec3 Sposition;
	vec3 Sscale;
	vec3 Srotation;
	vec4 Scolor;
	
	Sprite* image;
	DemoEngine_Animations::DemoTimer* timer;

	DemoEngine_TileMap::TileMap* tileMap;

public:
	EarthGame();
	~EarthGame();

	void Init() override;
	void Update() override;
	void DeInit() override;
};