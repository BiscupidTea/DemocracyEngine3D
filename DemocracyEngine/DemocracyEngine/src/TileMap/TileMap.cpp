#include "TileMap.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "../Animation/Frame.h"
#include "../Tools/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

namespace DemoEngine_TileMap
{
    TileMap::TileMap(vec3 newPosition, vec3 newRotation, vec3 newScale,
                     const char* tileSetFile, const vector<const char*>& tileMapFiles,
                     const char* tileMapImage): Entity2D(newPosition, newRotation, newScale)
    {
        LoadTileSet(tileSetFile);
        LoadTileMaps(tileMapFiles);
        Renderer::GetRender()->BindTexture(tileMapImage, tileMapTexture);
    }

    void TileMap::LoadTileMaps(const vector<const char*>& tileMapFiles)
    {
        layerCount = tileMapFiles.size();
        tileMap.clear();

        for (const auto& file : tileMapFiles)
        {
            TileMapLayer layerData = ReadSingleMap(file);

            tileMap.push_back(layerData);
        }

        for (int layerIndex = 0; layerIndex < tileMap.size(); ++layerIndex)
        {
            cout << "Layer " << layerIndex + 1 << ":\n";
            for (int y = 0; y < tileMap.at(layerIndex).y; ++y)
            {
                for (int x = 0; x < tileMap.at(layerIndex).x; ++x)
                {
                    cout << tileMap.at(layerIndex).getTileId(x, y) << " ";
                }
                cout << endl;
            }
            cout << "\n";
        }
    }

    void TileMap::LoadTileSet(const char* tileSetFile)
    {
        XMLDocument doc;
        if (doc.LoadFile(tileSetFile) != XML_SUCCESS)
        {
            cout << "Error loading file XML: " << tileSetFile << endl;
            return;
        }

        XMLElement* root = doc.FirstChildElement("tileset");
        if (!root)
        {
            cout << "Error: file is not a tileset file" << endl;
            return;
        }

        root->QueryIntAttribute("tilewidth", &tileWidth);
        root->QueryIntAttribute("tileheight", &tileHeight);

        root = doc.FirstChildElement("tileset")->FirstChildElement("image");
        root->QueryIntAttribute("width", &mapWidth);
        root->QueryIntAttribute("height", &mapHeight);

        vector<pair<vec2, vec2>> tileSetUV = CalculateUVCoordsInMap(mapHeight, mapWidth, tileHeight, tileWidth);

        root = doc.FirstChildElement("tileset");

        XMLElement* tileElement = root->FirstChildElement("tile");
        while (tileElement)
        {
            int tileId = tileElement->IntAttribute("id");
            bool hasCollision = false;

            XMLElement* properties = tileElement->FirstChildElement("properties");
            if (properties)
            {
                XMLElement* property = properties->FirstChildElement("property");
                while (property)
                {
                    const char* name = property->Attribute("name");
                    if (name && strcmp(name, "Obstacle") == 0)
                    {
                        const char* value = property->Attribute("value");
                        if (value && strcmp(value, "true") == 0)
                        {
                            hasCollision = true;
                            break;
                        }
                    }
                    property = property->NextSiblingElement("property");
                }
            }

            tileSet.push_back(Tile(tileId, hasCollision, tileSetUV.at(tileId).first, tileSetUV.at(tileId).second));
            tileElement = tileElement->NextSiblingElement("tile");
        }

        for (Tile currentTile : tileSet)
        {
            cout << "Tile loaded = ID: " << currentTile.id
                << " - hasCollision: " << currentTile.hasCollision
                << " - UV: (" << currentTile.leftTopUV.x << "," << currentTile.leftTopUV.x << ")"
                << " - UV: (" << currentTile.rightDowUV.y << "," << currentTile.rightDowUV.y << ")"
                << endl;
        }

        cout << "Loaded " << tileSet.size() << " tiles" << endl;
        cout << endl;
    }

    void TileMap::Draw()
    {
        for (size_t layerIndex = 0; layerIndex < tileMap.size(); ++layerIndex)
        {
            TileMapLayer& layer = tileMap[layerIndex];

            for (int y = 0; y < layer.y; ++y)
            {
                for (int x = 0; x < layer.x; ++x)
                {
                    int tileId = layer.getTileId(x, y);

                    if (tileId >= 0)
                    {
                        Tile& tile = tileSet[tileId];
                        Renderer::GetRender()->DrawTile(tile, x, y, tileMapTexture);
                    }
                }
            }
        }
    }

    bool TileMap::hasCollision(int layer, Entity2D entity)
    {
        return true;
    }

    bool TileMap::hasCollision(int layer, int x, int y, int width, int height)
    {
        return true;
    }

    TileMapLayer TileMap::ReadSingleMap(const char* filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error to open file: " << filename << endl;
            return TileMapLayer(0, 0);
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

        TileMapLayer mapData(width, height);

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                mapData.setTile(x, y, tempLayer[y][x]);
            }
        }

        return mapData;
    }

    vector<pair<vec2, vec2>> TileMap::CalculateUVCoordsInMap(int totalHeight, int totalWidth, int tileHeight,
                                                             int tileWidth)
    {
        vector<pair<vec2, vec2>> uvCoordsList;

        int numHeight = totalHeight / tileHeight;
        int numWidth = totalWidth / tileWidth;

        for (int i = 0; i < numHeight; ++i)
        {
            for (int j = 0; j < numWidth; ++j)
            {
                vec2 uv1 = {
                    static_cast<float>(j * tileWidth) / totalWidth, static_cast<float>(i * tileHeight) / totalHeight
                };
                vec2 uv2 = {
                    static_cast<float>((j + 1) * tileWidth) / totalWidth,
                    static_cast<float>((i + 1) * tileHeight) / totalHeight
                };

                uvCoordsList.push_back({uv1, uv2});
            }
        }

        return uvCoordsList;
    }
}
