#pragma once

#include <vector>
#include <initializer_list>

#include "base.hpp"

namespace TE::Core
{
	using RendererID = uint32_t;

	enum BUFFER_COMPONENTS : uint32_t
	{
		BUFFER_COMPO_X			= 1,
		BUFFER_COMPO_XY			= 2,
		BUFFER_COMPO_UV			= 2,
		BUFFER_COMPO_XYZ		= 3,
		BUFFER_COMPO_RGB		= 3,
		BUFFER_COMPO_RGBA		= 4,
		BUFFER_COMPO_XYZW		= 4,
		BUFFER_COMPO_MAT3		= 3,
		BUFFER_COMPO_MAT4		= 4,
	};

	enum BUFFER_STRIDE : uint32_t
	{
		BUFFER_STRIDE_BOOLEAN	= sizeof(bool),
		BUFFER_STRIDE_F1		= sizeof(float),
		BUFFER_STRIDE_F2		= sizeof(float) * 2,
		BUFFER_STRIDE_F3		= sizeof(float) * 3,
		BUFFER_STRIDE_F4		= sizeof(float) * 4,
		BUFFER_STRIDE_MAT3		= sizeof(float) * 3 * 3,
		BUFFER_STRIDE_MAT4		= sizeof(float) * 4 * 4,
	};

	struct BufferElements
	{
		int32_t Offset{ 0 };
		std::string Name{};
		BUFFER_STRIDE Stride{};
		bool Normalized{ false };
		BUFFER_COMPONENTS Components{};

		BufferElements() = default;
		BufferElements(const std::string& name, BUFFER_COMPONENTS components, BUFFER_STRIDE stride, bool normalized) : Name(name), Components(components), Stride(stride), Normalized(normalized) {}
		~BufferElements() = default;
	};

	class BufferLayout
	{
		public:
			BufferLayout() = default;
			BufferLayout(std::initializer_list<BufferElements> elements) : m_Elements(elements) { CalStride(); }
			~BufferLayout() = default;

			uint32_t GetStride() const { return m_Stride; }

			const std::vector<BufferElements>& GetElements() const { return m_Elements; }
			std::vector<BufferElements>::iterator begin() { return m_Elements.begin(); }
			std::vector<BufferElements>::iterator end() { return m_Elements.end(); }

		private:
			void CalStride()
			{
				m_Stride = 0;
				for( auto& element : m_Elements )
				{
					element.Offset = m_Stride;
					m_Stride += element.Stride;
				}
			}

		private:
			std::vector<BufferElements> m_Elements{};
			uint32_t m_Stride{ 0 };
	};

	class IVertexBuffer
	{
		public:
			IVertexBuffer() = default;
			virtual ~IVertexBuffer() = default;

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;
			virtual RendererID GetID() const = 0;

			virtual void SetData(const void* data, uint32_t size) = 0;
			virtual void SetLayout(const BufferLayout& layout) = 0;
			virtual const BufferLayout& GetLayout() const = 0;
	};

	class IIndexBuffer
	{
		public:
			IIndexBuffer() = default;
			virtual ~IIndexBuffer() = default;

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;
			virtual RendererID GetID() const = 0;
			virtual uint32_t GetCount() const = 0;
	};

	using VertexBuffer = IVertexBuffer;
	using IndexBuffer = IIndexBuffer;

	std::shared_ptr<VertexBuffer> CreateVertexBuffer(uint32_t alloca_size);
	std::shared_ptr<VertexBuffer> CreateVertexBuffer(float* data, uint32_t size);
	std::shared_ptr<IndexBuffer> CreateIndexBuffer(uint32_t* data, uint32_t count);
}
