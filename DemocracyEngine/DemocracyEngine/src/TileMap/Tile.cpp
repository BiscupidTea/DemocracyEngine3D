#include "Tile.h"

namespace DemoEngine_TileMap
{
    Tile::Tile(int id, bool hasCollision)
    {
        this->id = id;
        this->hasCollision = hasCollision;
    }
}