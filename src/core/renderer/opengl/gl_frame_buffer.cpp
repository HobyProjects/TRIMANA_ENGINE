#include "core_pch.hpp"

namespace TE::Core
{
	GL_FrameBuffer::GL_FrameBuffer(const FrameBufferSpecification& specification)
		: m_Specification(specification)
	{
		CreateFrame();
	}

	GL_FrameBuffer::~GL_FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_FrameBufferID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void GL_FrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
	}

	void GL_FrameBuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GL_FrameBuffer::ResizeFrame(uint32_t width, uint32_t height)
	{
		m_Specification.Width = width;
		m_Specification.Height = height;

		CreateFrame();
	}

	FrameBufferID GL_FrameBuffer::GetFrameBufferID() const
	{
		return m_FrameBufferID;
	}

	FrameBufferAttachmentID GL_FrameBuffer::GetColorAttachment() const
	{
		return m_ColorAttachment;
	}

	FrameBufferSpecification& GL_FrameBuffer::GetFrameSpecification()
	{
		return m_Specification;
	}

	void GL_FrameBuffer::CreateFrame()
	{
		if( m_FrameBufferID )
		{
			glDeleteFramebuffers(1, &m_FrameBufferID);
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteTextures(1, &m_DepthAttachment);
		}

		glCreateFramebuffers(1, &m_FrameBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

		if( glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE )
		{
			TE_CORE_WARN("Incompleted frame buffer generated!!!!");
		}
	}
}