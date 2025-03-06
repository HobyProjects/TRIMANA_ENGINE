#pragma once

#include "buffers.hpp"

namespace TE::Core
{
	class GL_VertexBuffer final : public IVertexBuffer
	{
		public:
			GL_VertexBuffer() = default;
			GL_VertexBuffer(uint32_t allocatorSize);
			GL_VertexBuffer(float* data, uint32_t dataSize);
			virtual ~GL_VertexBuffer();

			virtual void Bind() const override;
			virtual void Unbind() const override;
			virtual RendererID GetID() const override { return m_VertexBufferID; }
			virtual void SetData(const void* data, uint32_t size) override;
			virtual void SetLayout(const BufferLayout& layout) override;
			virtual const BufferLayout& GetLayout() const override { return m_Layout; }

		private:
			RendererID m_VertexBufferID{ 0 };
			BufferLayout m_Layout;
	};

	class GL_IndexBuffer final : public IindexBuffer
	{
		public:
			GL_IndexBuffer() = default;
			GL_IndexBuffer(uint32_t* data, uint32_t indicesCount);
			virtual ~GL_IndexBuffer();

			virtual void Bind() const override;
			virtual void Unbind() const override;
			virtual RendererID GetID() const override { return m_IndexBufferID; }
			virtual uint32_t GetCount() const override { return m_Count; }

		private:
			RendererID m_IndexBufferID{ 0 };
			uint32_t m_Count{ 0 };
	};
}