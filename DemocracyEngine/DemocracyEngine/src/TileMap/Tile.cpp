#include "Tile.h"

namespace DemoEngine_TileMap
{
    Tile::Tile(int id, bool hasCollision, glm::vec2 leftTopUV, glm::vec2 rightDowUV)
    {
        this->id = id;
        this->hasCollision = hasCollision;

        this->topRightUV = leftTopUV;
        this->topLeftUV = rightDowUV;
    }
}
