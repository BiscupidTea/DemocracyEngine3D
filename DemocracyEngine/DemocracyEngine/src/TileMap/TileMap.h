#pragma once
#include <vector>

#include "TileMapLayer.h"
#include "../Entities/Entity2D.h"

using namespace DemoEngine_Entities;

namespace DemoEngine_TileMap
{
	class EXPORT TileMap : public Entity2D
	{
	public:
		TileMap(vec3 newPosition, vec3 newRotation, vec3 newScale,
			const char* tileSetFile, const vector<const char*>& tileMapFiles,
			const char* tileMapImage, GLint textureFilter = GL_NEAREST);

		~TileMap();

		vector<TileMapLayer*> layers;

		bool CheckCollision(Entity2D a);
		void Draw();

	private:
		void LoadTileSet(const char* tileSetFile);

		vector<vector<vec2>> CalculateUVCoordsInMap(int HeightTiles, int WidthTiles, int totalHeight, int totalWidth, int tileHeight, int tileWidth);

		
		vector<Tile> tileSet;
		unsigned int tileMapTexture;

		//Map
		int mapPixelWidth;
		int mapPixelHeight;

		int tileSetTileHeight;
		int tileSetTileWidth;

		int mapTileHeight;
		int mapTileWidth;

		int layerCount;

		//Tiles
		int tilePixelWidth;
		int tilePixelHeight;
	};
}
