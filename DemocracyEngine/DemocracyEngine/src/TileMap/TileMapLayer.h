#pragma once
#include <vector>

class TileMapLayer
{
public:
    std::vector<int> layer;
    int y;
    int x;

    TileMapLayer(int width, int height);
    void setTile(int posX, int posY, int id);
    int getTileId(int posX, int posY);
};
