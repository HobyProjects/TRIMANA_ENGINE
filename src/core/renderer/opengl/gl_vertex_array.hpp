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
            virtual void EmplaceVtxBuffer(const std::shared_ptr<IVertexBuffer>& vtxBuffer) override;
            virtual void EmplaceIdxBuffer(const std::shared_ptr<IindexBuffer>& idxBuffer) override;
            virtual const std::vector<std::shared_ptr<IVertexBuffer>>& GetVtxBuffers() const override;
            virtual const std::shared_ptr<IindexBuffer>& GetIdexBuffer() const override;

        private:
            RendererID m_VertexArrayID{ 0 };
            std::vector<std::shared_ptr<IVertexBuffer>> m_VtxBuffers{};
            std::shared_ptr<IindexBuffer> m_IdexBuffer{};
	};
}