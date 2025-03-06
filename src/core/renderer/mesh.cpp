#include "core_pch.hpp"

namespace TE::Core
{
	Mesh::Mesh(float* vertices, uint32_t verticeSize, uint32_t* indices, uint32_t indicesCount, const BufferLayout& layout)
	{
		m_vertexBuffer = CreateVertexBuffer(vertices, verticeSize);
		m_vertexBuffer->SetLayout(layout);

		m_indexBuffer = CreateIndexBuffer(indices, indicesCount);
		m_vertexArray = CreateVertexArray();

		m_vertexArray->EmplaceVtxBuffer(m_vertexBuffer);
		m_vertexArray->EmplaceIdxBuffer(m_indexBuffer);
		m_IndicesCount = indicesCount;

	}

	void Mesh::Create(float* vertices, uint32_t verticeSize, uint32_t* indices, uint32_t indicesCount, const BufferLayout& layout)
	{
		m_vertexBuffer = CreateVertexBuffer(vertices, verticeSize);
		m_vertexBuffer->SetLayout(layout);

		m_indexBuffer = CreateIndexBuffer(indices, indicesCount);
		m_vertexArray = CreateVertexArray();

		m_vertexArray->EmplaceVtxBuffer(m_vertexBuffer);
		m_vertexArray->EmplaceIdxBuffer(m_indexBuffer);
		m_IndicesCount = indicesCount;
	}

	void Mesh::Render()
	{
		m_vertexArray->Bind();
		Renderer::Draw(m_IndicesCount);
		m_vertexArray->Unbind();
	}
}