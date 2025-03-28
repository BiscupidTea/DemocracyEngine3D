#include "TileMap.h"
#include "../Tools/tinyxml2.h"

using namespace tinyxml2;

namespace DemoEngine_TileMap
{
    TileMap::TileMap(vec3 newPosition, vec3 newRotation, vec3 newScale,
                     const char* tileSetFile, const vector<const char*>& tileMapFiles,
                     const char* tileMapImage, GLint textureFilter): Entity2D(newPosition, newRotation, newScale)
    {
        LoadTileSet(tileSetFile);

        for (int i = 0; i < tileMapFiles.size(); i++)
        {
            layers.emplace_back(new TileMapLayer(newPosition, newRotation, newScale, tileMapFiles.at(i), tileMapImage,
                                                 tileSet, textureFilter, tilePixelWidth, tilePixelHeight));
        }
    }

    TileMap::~TileMap()
    {
        for (TileMapLayer* layer : layers)
        {
            delete layer;
        }
        layers.clear();
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

        root->QueryIntAttribute("tilewidth", &tilePixelWidth);
        root->QueryIntAttribute("tileheight", &tilePixelHeight);
        
        if (root->QueryIntAttribute("spacing", &spacing) != XML_SUCCESS)
        {
            spacing = 0;
        }

        root = doc.FirstChildElement("tileset")->FirstChildElement("image");
        root->QueryIntAttribute("width", &mapPixelWidth);
        root->QueryIntAttribute("height", &mapPixelHeight);

        tileSetTileHeight = (mapPixelHeight / tilePixelHeight);
        tileSetTileWidth = (mapPixelWidth / tilePixelWidth);

        vector<vector<vec2>> tileSetUV = CalculateUVCoordsInMap(tileSetTileHeight, tileSetTileWidth, mapPixelHeight,
                                                                mapPixelWidth, tilePixelHeight,
                                                                tilePixelWidth);

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

            tileSet.push_back(Tile(tileId, hasCollision, tileSetUV.at(tileId)));
            tileElement = tileElement->NextSiblingElement("tile");
        }
    }

    void TileMap::Draw()
    {
        for (TileMapLayer* layer : layers)
        {
            layer->Draw();
        }
    }

    vector<vector<vec2>> TileMap::CalculateUVCoordsInMap(int HeightTiles, int WidthTiles, int totalHeight,
                                                         int totalWidth, int tileHeight, int tileWidth)
    {
        vector<vector<vec2>> uvCoordsList;

        for (int y = 0; y < HeightTiles; ++y)
        {
            for (int x = 0; x < WidthTiles; ++x)
            {
                vector<vec2> uvCoords;

                //topLeft
                uvCoords.push_back(vec2(static_cast<float>((x * tileWidth) + spacing * x) / totalWidth,
                                        1.0f - static_cast<float>((y * tileHeight) + spacing * y) / totalHeight));
                //TopRight
                uvCoords.push_back(vec2(static_cast<float>(((x + 1) * tileWidth) + spacing * x) / totalWidth,
                                        1.0f - static_cast<float>((y * tileHeight) + spacing * y) / totalHeight));
                //BottomLeft
                uvCoords.push_back(vec2(static_cast<float>((x * tileWidth) + spacing * x) / totalWidth,
                                        1.0f - static_cast<float>(((y + 1) * tileHeight) + spacing * y) / totalHeight));
                //BottomRight
                uvCoords.push_back(vec2(static_cast<float>(((x + 1) * tileWidth) + spacing * x) / totalWidth,
                                        1.0f - static_cast<float>(((y + 1) * tileHeight) + spacing * y) / totalHeight));

                uvCoordsList.push_back(uvCoords);
            }
        }

        return uvCoordsList;
    }

    bool TileMap::CheckCollision(Entity2D a)
    {
        for (int i = 0; i < layers.size(); i++)
        {
            if (layers[i]->hasCollision(a))
            {
                return true;
            }
        }
        return false;
    }
}
