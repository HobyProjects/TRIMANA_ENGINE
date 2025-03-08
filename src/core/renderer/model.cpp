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
		std::vector<float> vertices;
		std::vector<uint32_t> indices;

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

		std::shared_ptr<Mesh> newMesh = std::make_shared<Mesh>(
			vertices.data(),
			(uint32_t)vertices.size(),
			indices.data(),
			(uint32_t)indices.size(),
			BufferLayout({
				{ "a_Position", BUFFER_COMPO_XYZ, sizeof(VertexStructure), false, offsetof(VertexStructure, Position) },
				{ "a_TexCoords", BUFFER_COMPO_UV, sizeof(VertexStructure), false, offsetof(VertexStructure, TexCoords) },
				{ "a_Normal", BUFFER_COMPO_XYZ, sizeof(VertexStructure), false, offsetof(VertexStructure, Normal) }
			}));

		m_MeshList.emplace_back(newMesh);
		m_MeshTexturesMapping [newMesh] = mesh->mMaterialIndex;
	}

	void Model::LoadMaterials(const aiScene* scene, const std::filesystem::path& modelPath)
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
					std::filesystem::path modelFilePath(std::string(path.data));
					std::string filename = modelFilePath.filename().string();

					std::string enginePathA = modelPath.parent_path().string() + std::string("/textures/") + filename;
					std::string enginePathB = modelPath.parent_path().string() + std::string("/") + filename;

					TE_INFO("Texture path: {0}", enginePathB);
					if( std::filesystem::exists(enginePathB))
					{
						TE_CORE_INFO("Texture {0} found", enginePathB);
						m_TextureList [i] = CreateTexture2D(enginePathB);
					}
					else
					{
						TE_CORE_WARN("Texture {0} not found, Trying alternative path...", enginePathA);

						if( std::filesystem::exists(enginePathA) )
						{
							TE_CORE_INFO("Texture {0} found", enginePathA);
							m_TextureList [i] = CreateTexture2D(enginePathA);

						}
						else
						{
							TE_CORE_WARN("Texture {0} not found, Continuing with the default texture", enginePathA);
							m_TextureList [i] = CreateTexture2D(10, 10);
						}
					}
	
				}
			}
		}
	}

	bool Model::Load(const std::filesystem::path& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
		
		TE_ASSERT(scene, "Model {0} failed to load: {1}", path.string(), importer.GetErrorString());
		if( !scene ) return false;

		LoadNode(scene->mRootNode, scene);
		LoadMaterials(scene, path);

		return true;
	}

	void Model::Render()
	{
		for( size_t i = 0; i < m_MeshList.size(); i++ )
		{
			uint32_t materialIndex = m_MeshTexturesMapping[m_MeshList[i]];

			if( materialIndex < m_TextureList.size() && m_TextureList [materialIndex] )
			{
				m_TextureList [materialIndex]->Bind();
			}

			m_MeshList [i]->Render();
		}
	}
}