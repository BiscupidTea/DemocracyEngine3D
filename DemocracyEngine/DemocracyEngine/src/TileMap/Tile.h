#pragma once
namespace DemoEngine_TileMap
{
    static class EXPORT Tile
    {
    public:
        Tile(int id, bool hasCollision);

        int id;
        bool hasCollision;
    };
}
