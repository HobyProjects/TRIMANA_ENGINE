#pragma once

#include "buffers.hpp"
#include "texture.hpp"
#include "vertex_array.hpp"

namespace TE::Core
{
	struct VertexStructure
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	class Mesh
	{
	public:
		Mesh() = default;
		Mesh(float* vertices, uint32_t verticeSize, uint32_t* indices, uint32_t indicesCount);
		~Mesh() = default;

		void Create(float* vertices, uint32_t verticeSize, uint32_t* indices, uint32_t indicesCount);
		void Render();

	private:
		std::shared_ptr<IVertexBuffer> m_vertexBuffer{ nullptr };
		std::shared_ptr<IIndexBuffer> m_indexBuffer{ nullptr };
		std::shared_ptr<IVertexArray> m_vertexArray{ nullptr };
		uint32_t m_IndicesCount{ 0 };
	};
}