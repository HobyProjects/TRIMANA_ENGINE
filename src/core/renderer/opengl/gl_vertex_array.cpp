#include "core_pch.hpp"

namespace TE::Core
{
	GL_VertexArray::GL_VertexArray()
	{
		glGenVertexArrays(1, &m_VertexArrayID);
	}

	GL_VertexArray::~GL_VertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void GL_VertexArray::Bind() const
	{
		glBindVertexArray(m_VertexArrayID);
	}

	void GL_VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	RendererID GL_VertexArray::GetID() const
	{
		return m_VertexArrayID;
	}

	void GL_VertexArray::EmplaceVtxBuffer(const std::shared_ptr<VertexBuffer>& vtxBuffer)
	{
		glBindVertexArray(m_VertexArrayID);
		vtxBuffer->Bind();
		const auto& layout = vtxBuffer->GetLayout();
		const auto& elements = layout.GetElements();
		uint32_t layout_index{ 0 };

		for( auto& element : elements )
		{
			glEnableVertexAttribArray(layout_index);
			glVertexAttribPointer(
				layout_index,
				static_cast<GLint>( element.Components ),
				GL_FLOAT,
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*) element.Offset
			);
		}

		m_VtxBuffers.emplace_back(vtxBuffer);
	}

	void GL_VertexArray::EmplaceIdxBuffer(const std::shared_ptr<IndexBuffer>& idxBuffer)
	{
		glBindVertexArray(m_VertexArrayID);
		idxBuffer->Bind();
		m_IdexBuffer = idxBuffer;
	}

	const std::vector<std::shared_ptr<VertexBuffer>>& GL_VertexArray::GetVtxBuffers() const
	{
		return m_VtxBuffers;
	}

	const std::shared_ptr<IndexBuffer>& GL_VertexArray::GetIdexBuffer() const
	{
		return m_IdexBuffer;
	}
}

