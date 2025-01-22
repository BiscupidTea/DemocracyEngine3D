#pragma once
#include <glm/vec2.hpp>
#include <vector>

#include "../Tools/Export.h"

namespace DemoEngine_TileMap
{
	class EXPORT Tile
	{
	public:
		Tile(int id, bool hasCollision,std::vector<glm::vec2> UV);

		int id;

		glm::vec2 topRightUV;
		glm::vec2 topLeftUV;
		glm::vec2 bottomRightUV;
		glm::vec2 bottomleftUV;
		
		bool hasCollision;
	};
}
