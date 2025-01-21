#pragma once
#include <vector>

#include "Tile.h"
#include "TileMapLayer.h"
#include "../Entities/Entity2D.h"

using namespace DemoEngine_Entities;


namespace DemoEngine_TileMap
{
    class EXPORT TileMap : public Entity2D
    {
    public:
        TileMap(vec3 newPosition, vec3 newRotation, vec3 newScale, const char* tileSetFile, const vector<const char*>& tileMapFiles, const char* tileMapImage);

        void Draw();

        bool hasCollision(int layer, Entity2D entity);
        bool hasCollision(int layer, int x, int y, int width, int height);


    private:
        void LoadTileMaps(const vector<const char*>& tileMapFiles);
        void LoadTileSet(const char* tileSetFile);
        
        TileMapLayer ReadSingleMap(const char* filename);
        vector<pair<vec2, vec2>>  CalculateUVCoordsInMap(int totalHeight, int totalWidth, int tileHeight, int tileWidth);
        
        vector<TileMapLayer> tileMap;
        vector<Tile> tileSet;

        unsigned int tileMapTexture;
        
        //Map
        int mapWidth;
        int mapHeight;
        int layerCount;

        //Tiles
        int tileWidth;
        int tileHeight;
    };
}
