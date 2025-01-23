#include "TileMapLayer.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "../Tools/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

namespace DemoEngine_TileMap
{
    TileMapLayer::TileMapLayer(vec3 newPosition, vec3 newRotation, vec3 newScale, const char* tileMapFiles,
                               const char* tileMapImage, vector<Tile> tileSet, GLint textureFilter) : Entity2D(
        newPosition, newRotation, newScale), tileMap(0, 0)
    {
        this->tileSet = tileSet;
        tileMap = ReadMap(tileMapFiles);

        const int quadDataLenght = 36; //(position*3 + colors*4 + texture coords*2) * 4
        const int quadindexDataLenght = 6; // indices = 0, 1, 3, 1, 2, 3
        const int vertexPerQuad = 4;

        vertexSize = quadDataLenght * mapTileHeight * mapTileWidth;
        vector<float> vertexVector;

        for (int y = 0; y < mapTileHeight; y++)
        {
            for (int x = 0; x < mapTileWidth; x++)
            {
                int tileId = tileMap.getTileId(x, y);

                AddToVertex(static_cast<float>(1 + x), static_cast<float>(1 - y), tileId,
                            tileId >= 0 ? tileSet.at(tileMap.getTileId(x, y)).topRightUV : vec2(0, 0), vertexVector);
                AddToVertex(static_cast<float>(1 + x), static_cast<float>(0 - y), tileId,
                            tileId >= 0 ? tileSet.at(tileMap.getTileId(x, y)).bottomRightUV : vec2(0, 0), vertexVector);
                AddToVertex(static_cast<float>(0 + x), static_cast<float>(0 - y), tileId,
                            tileId >= 0 ? tileSet.at(tileMap.getTileId(x, y)).bottomleftUV : vec2(0, 0), vertexVector);
                AddToVertex(static_cast<float>(0 + x), static_cast<float>(1 - y), tileId,
                            tileId >= 0 ? tileSet.at(tileMap.getTileId(x, y)).topLeftUV : vec2(0, 0), vertexVector);
            }
        }

        indexSize = quadindexDataLenght * mapTileHeight * mapTileWidth;
        vector<int> indicesVector;
        for (int i = 0; i < mapTileWidth * mapTileHeight; i++)
        {
            indicesVector.push_back(0 + (vertexPerQuad * i));
            indicesVector.push_back(1 + (vertexPerQuad * i));
            indicesVector.push_back(3 + (vertexPerQuad * i));
            indicesVector.push_back(1 + (vertexPerQuad * i));
            indicesVector.push_back(2 + (vertexPerQuad * i));
            indicesVector.push_back(3 + (vertexPerQuad * i));
        }

        vertex = new float[vertexSize];
        std::copy(std::begin(vertexVector), std::end(vertexVector), vertex);

        indices = new int[indexSize];
        std::copy(std::begin(indicesVector), std::end(indicesVector), indices);

        Renderer::GetRender()->CreateSprite(VBO, VAO, EBO, vertex, indices, vertexSize, indexSize);
        Renderer::GetRender()->BindTexture(tileMapImage, tileMapTexture, textureFilter);
    }

    TileMapLayer::~TileMapLayer()
    {
        delete[] vertex;
        delete[] indices;
    }

    void TileMapLayer::AddToVertex(float x, float y, int tileId, vec2 UvCoord, vector<float>& vertexVector)
    {
        //position
        vertexVector.push_back(x);
        vertexVector.push_back(y);
        vertexVector.push_back(0.0f);

        //color
        vertexVector.push_back(1.0f);
        vertexVector.push_back(1.0f);
        vertexVector.push_back(1.0f);
        vertexVector.push_back(tileId >= 0 ? 1.0f : 0.0f);

        //UV
        vertexVector.push_back(UvCoord.x);
        vertexVector.push_back(UvCoord.y);
    }

    void TileMapLayer::Draw()
    {
        Renderer::GetRender()->DrawTexture(VAO, indexSize, color, model, tileMapTexture);
    }

    bool TileMapLayer::hasCollision(int layer, Entity2D entity)
    {
        return true;
    }

    bool TileMapLayer::hasCollision(int layer, int x, int y, int width, int height)
    {
        return true;
    }

    TileMapLayerData TileMapLayer::ReadMap(const char* filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error to open file: " << filename << endl;
            return TileMapLayerData(0, 0);
        }

        vector<vector<int>> tempLayer;
        string line;

        while (getline(file, line))
        {
            vector<int> row;
            stringstream ss(line);
            string cell;
            while (getline(ss, cell, ','))
            {
                row.push_back(stoi(cell));
            }
            tempLayer.push_back(row);
        }

        file.close();

        int width = tempLayer[0].size();
        int height = tempLayer.size();

        mapTileHeight = height;
        mapTileWidth = width;

        TileMapLayerData mapData(width, height);

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                mapData.setTile(x, y, tempLayer[y][x]);
            }
        }

        return mapData;
    }
}
