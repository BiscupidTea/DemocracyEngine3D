#include "../Mesh/Importer3D.h"
#include "Model3D.h"

using namespace DemoEngine_Importer;

namespace DemoEngine_Entities
{
	Model3D::Model3D(const char* path)
	{
		try
		{
			std::pair<std::vector<std::vector<Vertex>>, std::vector<std::vector<unsigned int>>> data = Importer3D::ImportModel(path);

			const std::vector<std::vector<Vertex>>& vertices = data.first;
			const std::vector<std::vector<unsigned int>>& indices = data.second;

			for (size_t i = 0; i < vertices.size(); ++i)
				AddMesh(vertices[i], indices[i]);
		}
		catch (const std::exception&)
		{
		
		}

	}

	void Model3D::AddMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	{
		_vertices.push_back(vertices);
		_indices.push_back(indices);
	}
}
