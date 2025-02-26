#include "core_pch.hpp"

namespace TE::Core
{
	std::shared_ptr<Texture2D> TE::Core::CreateTexture2D(uint32_t width, uint32_t Height)
	{
		switch( Renderer::API() )
		{
			case RENDERER_API_OPENGL:	return std::make_shared<GL_Texture>(width, Height);
			case RENDERER_API_VULKAN:	TE_ASSERT(false, "Vulkan API is not implemented yet!"); return nullptr;
			case RENDERER_API_DIRECTX:	TE_ASSERT(false, "DirectX API is not implemented yet!"); return nullptr;
			default:					return nullptr;
		};
	}

	std::shared_ptr<Texture2D> CreateTexture2D(const std::filesystem::path& textureFile, bool flip)
	{
		switch( Renderer::API() )
		{
			case RENDERER_API_OPENGL:	return std::make_shared<GL_Texture>(textureFile, flip);
			case RENDERER_API_VULKAN:	TE_ASSERT(false, "Vulkan API is not implemented yet!"); return nullptr;
			case RENDERER_API_DIRECTX:	TE_ASSERT(false, "DirectX API is not implemented yet!"); return nullptr;
			default:					return nullptr;
		};
	}
}