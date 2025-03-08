#pragma once

#include <vector>
#include <filesystem>
#include <unordered_map>

#include "mesh.hpp"
#include "texture.hpp"
#include "shader.hpp"

namespace TE::Core
{
	using TextureIndex = uint32_t;

	class Model
	{
		public:
			Model() = default;
			~Model() = default;

			bool Load(const std::filesystem::path& path);
			void Render();

		private:
			void LoadNode(aiNode* node, const aiScene* scene);
			void LoadMesh(aiMesh* mesh, const aiScene* scene);
			void LoadMaterials(const aiScene* scene, const std::filesystem::path& modelPath);

		private:
			std::vector<std::shared_ptr<Mesh>> m_MeshList;
			std::vector<std::shared_ptr<ITexture>> m_TextureList;
			std::unordered_map<std::shared_ptr<Mesh>, TextureIndex> m_MeshTexturesMapping;
	};
}