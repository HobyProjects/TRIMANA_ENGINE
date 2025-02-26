#pragma once

#include "frame_buffer.hpp"

namespace TE::Core
{
	using FrameBufferID = uint32_t;
	using FrameBufferAttachmentID = uint32_t;

	class GL_FrameBuffer : public IFrameBuffer
	{
        public:
            GL_FrameBuffer() = default;
            GL_FrameBuffer(const FrameBufferSpecification& specification);
            virtual ~GL_FrameBuffer();

            virtual void Bind() const override;
            virtual void Unbind() const override;
            virtual void ResizeFrame(uint32_t width, uint32_t Height) override;
            virtual FrameBufferID GetFrameBufferID() const override;
            virtual FrameBufferAttachmentID GetColorAttachment() const override;
            virtual FrameBufferSpecification& GetFrameSpecification() override;

        protected:
            virtual void CreateFrame() override;

        private:
            FrameBufferID m_FrameBufferID{ 0 };
            FrameBufferAttachmentID m_ColorAttachment{ 0 };
            FrameBufferAttachmentID m_DepthAttachment{ 0 };
            FrameBufferSpecification m_Specification{};
	};
}