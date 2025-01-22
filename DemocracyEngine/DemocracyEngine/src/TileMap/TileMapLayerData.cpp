#include  "TileMapLayerData.h"

#include <iostream>

TileMapLayerData::TileMapLayerData(int width, int height)
{
	x = width;
	y = height;
	layer.resize(x * y, 0);
}

void TileMapLayerData::setTile(int posX, int posY, int id)
{
	layer[(posY * x) + posX] = id;
}

int TileMapLayerData::getTileId(int posX, int posY)
{
		return layer[(posY * x) + posX];
}
