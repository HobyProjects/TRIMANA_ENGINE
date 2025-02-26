#pragma once

#include <filesystem>
#include "texture.hpp"

namespace TE::Core
{
	class GL_Texture final : public ITexture
	{
		public:
			GL_Texture(uint32_t width, uint32_t Height);
			GL_Texture(const std::filesystem::path& textureFile, bool Flip = true);
			virtual ~GL_Texture();

			virtual void Bind() const override;
			virtual void Bind(uint32_t slot) const override;
			virtual void Unbind() const override;

			virtual TextureID GetID() const override;
			virtual const TextureSpecification& GetSpecification() const override;

		private:
			TextureSpecification m_Specification{};
			TextureID m_TextureID{ 0 };
			bool m_FromFile{ false };
	};
}