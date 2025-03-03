#pragma once

#include <memory>
#include "buffers.hpp"

namespace TE::Core
{
	class IVertexArray
	{
		public:
			IVertexArray() = default;
			virtual ~IVertexArray() = default;

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual RendererID GetID() const = 0;
			virtual void EmplaceVtxBuffer(const std::shared_ptr<VertexBuffer>& vtxBuffer) = 0;
			virtual void EmplaceIdxBuffer(const std::shared_ptr<IndexBuffer>& idxBuffer) = 0;
			virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVtxBuffers() const = 0;
			virtual const std::shared_ptr<IndexBuffer>& GetIdexBuffer() const = 0;
	};

	std::shared_ptr<IVertexArray> CreateVertexArray();
}