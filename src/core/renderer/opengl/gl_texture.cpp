#include "core_pch.hpp"

namespace TE::Core
{
	GL_Texture::GL_Texture(uint32_t width, uint32_t height)
	{
		m_Specification.Width					= width;
		m_Specification.Height					= height;
		m_Specification.NumberOfChannels		= GL_RGBA;
		m_Specification.InternalDataFormat		= GL_RGBA8;
		m_Specification.TextureDataFormat		= GL_RGBA;

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
		TE_ASSERT(std::filesystem::exists(textureFile), "Unable to load texture file : {0}", textureFile.string());
		stbi_set_flip_vertically_on_load(Flip);
		m_Specification.TextureData = stbi_load(textureFile.string().c_str(), &m_Specification.Width, &m_Specification.Height, &m_Specification.NumberOfChannels, NULL);
		TE_ASSERT(m_Specification.TextureData, "Texture loading error!!");

		if( m_Specification.NumberOfChannels == 4 )
		{
			m_Specification.InternalDataFormat = GL_RGBA8;
			m_Specification.TextureDataFormat = GL_RGBA;
		}
		else
		{
			m_Specification.InternalDataFormat = GL_RGB8;
			m_Specification.TextureDataFormat = GL_RGB;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, m_Specification.InternalDataFormat, m_Specification.Width, m_Specification.Height, 0, m_Specification.TextureDataFormat, GL_UNSIGNED_BYTE, m_Specification.TextureData);
		glGenerateMipmap(GL_TEXTURE_2D);
		m_FromFile = true;
	}

	GL_Texture::~GL_Texture()
	{
		( m_FromFile ) ? stbi_image_free(m_Specification.TextureData) : delete[] m_Specification.TextureData;
		glDeleteTextures(1, &m_TextureID);
	}

	void GL_Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void GL_Texture::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_TextureID);
	}

	void GL_Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	TextureID GL_Texture::GetID() const
	{
		return m_TextureID;
	}

	const TextureSpecification& GL_Texture::GetSpecification() const
	{
		return m_Specification;
	}
}