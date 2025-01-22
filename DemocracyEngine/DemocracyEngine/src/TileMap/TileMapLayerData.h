#pragma once
#include <vector>

class TileMapLayerData
{
public:
    std::vector<int> layer;
    int y;
    int x;

    TileMapLayerData(int width, int height);
    void setTile(int posX, int posY, int id);
    int getTileId(int posX, int posY);
};
