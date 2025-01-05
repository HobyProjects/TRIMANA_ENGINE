#include "core_pch.hpp"

namespace TE::Core
{
	GL_Texture::GL_Texture(uint32_t width, uint32_t height)
	{
		m_Specification.Width = width;
		m_Specification.Height = height;
		m_Specification.NumberOfChannels = GL_RGBA;
		m_Specification.InternalDataFormat = GL_RGBA8;
		m_Specification.TextureDataFormat = GL_RGBA;

		uint32_t textureAllocateSize = m_Specification.Width * m_Specification.Height * m_Specification.NumberOfChannels;
		m_Specification.TextureData = new uint8_t [textureAllocateSize];
		std::memset(m_Specification.TextureData, 255, textureAllocateSize);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, m_Specification.InternalDataFormat, m_Specification.Width, m_Specification.Height, 0, m_Specification.TextureDataFormat, GL_UNSIGNED_BYTE, m_Specification.TextureData);
		glGenerateMipmap(GL_TEXTURE_2D);
		m_FromFile = false;
	}

	GL_Texture::GL_Texture(const std::filesystem::path& textureFile, bool Flip)
	{
	}

	GL_Texture::~GL_Texture()
	{

	}

	void GL_Texture::Bind(uint32_t slot) const
	{

	}

	void GL_Texture::UnBind() const
	{

	}

	TextureID GL_Texture::GetID() const
	{

	}

	const TextureSpecification& GL_Texture::GetSpecification() const
	{
		// TODO: insert return statement here
	}
}