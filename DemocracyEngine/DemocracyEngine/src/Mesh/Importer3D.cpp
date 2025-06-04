#include "Importer3D.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

namespace DemoEngine_Importer
{
	std::pair<
		std::vector<std::vector<Vertex>>,
		std::vector<std::vector<unsigned int>>
	> Importer3D::ImportModel(const std::string& path)
	{
		std::vector<std::vector<Vertex>> allVertices;
		std::vector<std::vector<unsigned int>> allIndices;

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path,
			aiProcess_Triangulate |
			aiProcess_FlipUVs |
			aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return { allVertices, allIndices };
		}

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;

			for (unsigned int v = 0; v < mesh->mNumVertices; v++)
			{
				Vertex vertex;
				vertex.position = glm::vec3(
					mesh->mVertices[v].x,
					mesh->mVertices[v].y,
					mesh->mVertices[v].z);

				vertex.normal = mesh->HasNormals()
					? glm::vec3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z)
					: glm::vec3(0.0f);

				vertex.texCoords = mesh->mTextureCoords[0]
					? glm::vec2(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y)
					: glm::vec2(0.0f);

				vertex.tangent = mesh->HasTangentsAndBitangents()
					? glm::vec3(mesh->mTangents[v].x, mesh->mTangents[v].y, mesh->mTangents[v].z)
					: glm::vec3(0.0f);

				vertex.bitangent = mesh->HasTangentsAndBitangents()
					? glm::vec3(mesh->mBitangents[v].x, mesh->mBitangents[v].y, mesh->mBitangents[v].z)
					: glm::vec3(0.0f);

				vertices.push_back(vertex);
			}

			for (unsigned int f = 0; f < mesh->mNumFaces; f++)
			{
				aiFace face = mesh->mFaces[f];
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}

			allVertices.push_back(vertices);
			allIndices.push_back(indices);
		}

		return { allVertices, allIndices };
	}
}
