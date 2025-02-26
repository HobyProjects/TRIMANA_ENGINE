#pragma once

#include <filesystem>
#include <memory>

namespace TE::Core
{
	using TextureID = uint32_t;

	struct TextureSpecification
	{
		uint8_t* TextureData{ nullptr };
		int32_t Width{ 0 }, Height{ 0 }, NumberOfChannels{ 0 };
		uint32_t InternalDataFormat{ 0 }, TextureDataFormat{ 0 };
	};

	class ITexture
	{
		public:
			ITexture() = default;
			virtual ~ITexture() = default;

			virtual void Bind() const = 0;
			virtual void Bind(uint32_t slot) const = 0;
			virtual void Unbind() const = 0;

			virtual TextureID GetID() const = 0;
			virtual const TextureSpecification& GetSpecification() const = 0;
	};

	using Texture2D = ITexture;
	std::shared_ptr<Texture2D> CreateTexture2D(uint32_t width, uint32_t Height);
	std::shared_ptr<Texture2D> CreateTexture2D(const std::filesystem::path& textureFile, bool flip = true);
}