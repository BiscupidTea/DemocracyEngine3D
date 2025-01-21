#include  "TileMapLayer.h"

#include <iostream>

TileMapLayer::TileMapLayer(int width, int height)
{
        x = width;
        y = height;
        layer.resize(x * y, 0);
}

void TileMapLayer::setTile(int posX, int posY, int id)
{
        layer[posY * x + posX] = id;
}

int TileMapLayer::getTileId(int posX, int posY)
{
        if (posX >= 0 && posX < x && posY >= 0 && posY < y) {
                return layer[posY * x + posX];
        } else {
                std::cout << "Error out of bounds" << std::endl;
                return -1;
        }
}
