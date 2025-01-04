#pragma once

#include "vertex_array.hpp"

namespace TE::Core
{
	class GL_VertexArray : public IVertexArray
	{
        public:
            GL_VertexArray();
            virtual ~GL_VertexArray();

            virtual void Bind() const override;
            virtual void Unbind() const override;

            virtual RendererID GetID() const override;
            virtual void EmplaceVtxBuffer(const std::shared_ptr<VertexBuffer>& vtxBuffer) override;
            virtual void EmplaceIdxBuffer(const std::shared_ptr<IndexBuffer>& idxBuffer) override;
            virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVtxBuffers() const override;
            virtual const std::shared_ptr<IndexBuffer>& GetIdexBuffer() const override;

        private:
            RendererID m_VertexArrayID{ 0 };
            std::vector<std::shared_ptr<VertexBuffer>> m_VtxBuffers{};
            std::shared_ptr<IndexBuffer> m_IdexBuffer{};
	};
}