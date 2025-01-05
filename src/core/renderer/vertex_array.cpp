#include "core_pch.hpp"

namespace TE::Core
{
	std::shared_ptr<VertexArray> CreateVertexArray()
	{
		switch( Renderer::API() )
		{
			case RENDERER_API_OPENGL:		return std::make_shared<GL_VertexArray>();
			case RENDERER_API_VULKAN:		TE_ASSERT(false, "Vulkan API is not yet supported"); return nullptr;
			case RENDERER_API_DIRECTX:		TE_ASSERT(false, "DirectX API is not yet supported"); return nullptr;
			default:						return nullptr;
		};
	}
}