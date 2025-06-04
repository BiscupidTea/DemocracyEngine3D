#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace DemoEngine_Entities
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
		glm::vec3 tangent;
		glm::vec3 bitangent;
	};

	class Model3D
	{
	public:
		Model3D(const char* path);

		const std::vector<std::vector<Vertex>>& GetVertices() const { return _vertices; }
		const std::vector<std::vector<unsigned int>>& GetIndices() const { return _indices; }

	private:
		void AddMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

	private:
		std::vector<std::vector<Vertex>> _vertices;
		std::vector<std::vector<unsigned int>> _indices;
	};
}
