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
	layer[(posY * x) + posX] = id;
}

int TileMapLayer::getTileId(int posX, int posY)
{
		return layer[(posY * x) + posX];
}
