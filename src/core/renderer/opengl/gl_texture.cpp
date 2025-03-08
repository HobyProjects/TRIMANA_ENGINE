#include "core_pch.hpp"

namespace TE::Core
{
	GL_Texture::GL_Texture(uint32_t width, uint32_t Height)
	{
		m_Specification.Width					= width;
		m_Specification.Height					= Height;
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
		TE_ASSERT(std::filesystem::exists(textureFile), "Unable to load texture file {0}", textureFile.string());
		int32_t loaderFlags = ( Flip ) ? ( SOIL_LOAD_RGBA | SOIL_FLAG_INVERT_Y | SOIL_FLAG_DDS_LOAD_DIRECT | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_COMPRESS_TO_DXT ) : ( SOIL_LOAD_RGBA | SOIL_FLAG_DDS_LOAD_DIRECT | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_COMPRESS_TO_DXT );
		m_TextureID = SOIL_load_OGL_texture(textureFile.string().c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, loaderFlags);
		TE_ASSERT(m_TextureID, "Unable to load texture file {0}; {1}", textureFile.string(), SOIL_last_result());

		m_FromFile = true;
		if( m_Specification.TextureData )
			TE_CORE_INFO("Texture loader: {0} loaded successfully!!", textureFile.string());
	}

	GL_Texture::~GL_Texture()
	{
		( m_FromFile ) ? SOIL_free_image_data(m_Specification.TextureData) : delete[] m_Specification.TextureData;
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