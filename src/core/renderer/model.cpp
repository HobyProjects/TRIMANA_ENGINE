#include "core_pch.hpp"

namespace TE::Core
{
	void Model::LoadNode(aiNode* node, const aiScene* scene)
	{
		for( size_t i = 0; i < node->mNumMeshes; i++ )
		{
			LoadMesh(scene->mMeshes [node->mMeshes [i]], scene);
		}

		for( size_t i = 0; i < node->mNumChildren; i++ )
		{
			LoadNode(node->mChildren [i], scene);
		}
	}

	void Model::LoadMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<GLfloat> vertices;
		std::vector<unsigned int> indices;

		for( size_t i = 0; i < mesh->mNumVertices; i++ )
		{
			vertices.insert(vertices.end(), { mesh->mVertices [i].x, mesh->mVertices [i].y, mesh->mVertices [i].z });
			if( mesh->mTextureCoords [0] )
			{
				vertices.insert(vertices.end(), { mesh->mTextureCoords [0][i].x, mesh->mTextureCoords [0][i].y });
			}
			else
			{
				vertices.insert(vertices.end(), { 0.0f, 0.0f });
			}
			vertices.insert(vertices.end(), { -mesh->mNormals [i].x, -mesh->mNormals [i].y, -mesh->mNormals [i].z });
		}

		for( size_t i = 0; i < mesh->mNumFaces; i++ )
		{
			aiFace face = mesh->mFaces [i];
			for( size_t j = 0; j < face.mNumIndices; j++ )
			{
				indices.push_back(face.mIndices [j]);
			}
		}

		std::shared_ptr<Mesh> newMesh = std::make_shared<Mesh>();
		newMesh->Create(vertices.data(), sizeof(vertices[0]) * vertices.size(), indices.data(), indices.size());
		m_MeshList.emplace_back(newMesh);
		m_MeshTexturesMapping [newMesh] = mesh->mMaterialIndex;
	}

	void Model::LoadMaterials(const aiScene* scene)
	{
		m_TextureList.resize(scene->mNumMaterials);

		for( size_t i = 0; i < scene->mNumMaterials; i++ )
		{
			aiMaterial* material = scene->mMaterials [i];

			m_TextureList [i] = nullptr;

			if( material->GetTextureCount(aiTextureType_DIFFUSE) )
			{
				aiString path;
				if( material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS )
				{
					int idx = std::string(path.data).rfind("\\");
					std::string filename = std::string(path.data).substr(idx + 1);
					std::string texPath = std::string("textures/") + filename;
					m_TextureList [i] = CreateTexture2D(texPath);
				}
			}

			if( !m_TextureList [i] )
			{
				m_TextureList [i] = CreateTexture2D(1, 1);
			}
		}
	}

	bool Model::Load(const std::filesystem::path& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
		TE_ASSERT(scene, "Model {0} failed to load: {1}", path.string(), importer.GetErrorString());
		LoadNode(scene->mRootNode, scene);
		LoadMaterials(scene);
	}

	void Model::Render()
	{
		for( size_t i = 0; i < m_MeshList.size(); i++ )
		{
			unsigned int materialIndex = m_MeshTexturesMapping[m_MeshList[i]];

			if( materialIndex < m_TextureList.size() && m_TextureList [materialIndex] )
			{
				m_TextureList [materialIndex]->Bind();
			}

			m_MeshList [i]->Render();
		}
	}
}