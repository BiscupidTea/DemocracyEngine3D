#pragma once
#include <vector>

#include "Tile.h"
#include "TileMapLayerData.h"
#include "../Entities/Entity2D.h"

using namespace DemoEngine_Entities;


namespace DemoEngine_TileMap
{
    class EXPORT TileMapLayer : public Entity2D
    {
    public:
        TileMapLayer(vec3 newPosition, vec3 newRotation, vec3 newScale, const char* tileMapFiles,
                     const char* tileMapImage, vector<Tile> tileSet, GLint textureFilter, int tilePixelWidth,
                     int tilePixelHeight);
        ~TileMapLayer();

        void Draw();

        bool hasCollision(Entity2D entity);

    private:
        TileMapLayerData ReadMap(const char* filename);
        void AddToVertex(float x, float y, int tileId, vec2 UvCoord, vector<float>& vertexVector);

        TileMapLayerData tileMap;
        vector<Tile> tileSet;

        unsigned int tileMapTexture;

        //Map
        int mapTileHeight;
        int mapTileWidth;

        //Tile
        int tilePixelWidth;
        int tilePixelHeight;

        float* vertex;
        int* indices;
    };
}
