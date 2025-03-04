#include "core_pch.hpp"

namespace TE::Core
{
	Mesh::Mesh(float* vertices, uint32_t verticeSize, uint32_t* indices, uint32_t indicesCount)
	{
		m_vertexBuffer = CreateVertexBuffer(vertices, verticeSize);
		m_vertexBuffer->SetLayout({
			{"a_Position", BUFFER_COMPO_XYZ, sizeof(VertexStructure), false, offsetof(VertexStructure, Position)},
			{"a_Normal", BUFFER_COMPO_XYZ, sizeof(VertexStructure), false, offsetof(VertexStructure, Normal)},
			{"a_TexCoords", BUFFER_COMPO_UV, sizeof(VertexStructure), false, offsetof(VertexStructure, TexCoords)},
		});

		m_indexBuffer = CreateIndexBuffer(indices, indicesCount);
		m_vertexArray = CreateVertexArray();
		m_vertexArray->EmplaceVtxBuffer(m_vertexBuffer);
		m_vertexArray->EmplaceIdxBuffer(m_indexBuffer);

	}

	void Mesh::Create(float* vertices, uint32_t verticeSize, uint32_t* indices, uint32_t indicesCount)
	{
		m_vertexBuffer = CreateVertexBuffer(vertices, verticeSize);
		m_vertexBuffer->SetLayout({
			{"a_Position", BUFFER_COMPO_XYZ, sizeof(VertexStructure), false, offsetof(VertexStructure, Position)},
			{"a_Normal", BUFFER_COMPO_XYZ, sizeof(VertexStructure), false, offsetof(VertexStructure, Normal)},
			{"a_TexCoords", BUFFER_COMPO_UV, sizeof(VertexStructure), false, offsetof(VertexStructure, TexCoords)},
		});

		m_indexBuffer = CreateIndexBuffer(indices, indicesCount);
		m_vertexArray = CreateVertexArray();
		m_vertexArray->EmplaceVtxBuffer(m_vertexBuffer);
		m_vertexArray->EmplaceIdxBuffer(m_indexBuffer);
	}

	void Mesh::Render()
	{
		m_vertexArray->Bind();
		Renderer::Draw(m_IndicesCount);
		m_vertexArray->Unbind();
	}
}