#pragma once
#include <vector>
#include <string>
#include "../Entities/Model3D.h"

using namespace DemoEngine_Entities;

namespace DemoEngine_Importer
{
    class Importer3D
    {
    public:
        static std::pair<
            std::vector<std::vector<Vertex>>,
            std::vector<std::vector<unsigned int>>
        > ImportModel(const std::string& path);
    };
}
