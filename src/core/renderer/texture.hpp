#pragma once

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

			virtual void Bind(uint32_t slot) const = 0;
			virtual void UnBind() const = 0;

			virtual TextureID GetID() const = 0;
			virtual const TextureSpecification& GetSpecification() const = 0;
	};
}