#include "core_pch.hpp"

namespace TE::Core
{
	std::shared_ptr<FrameBuffer> CreateFrameBuffer(const FrameBufferSpecification& specification)
	{
		switch( Renderer::API() )
		{
			case RENDERER_API_OPENGL:		return std::make_shared<GL_FrameBuffer>(specification);
			case RENDERER_API_VULKAN:		throw UnimplementedFeatureException("Vulkan FrameBuffer not implemented yet"); return nullptr;
			case RENDERER_API_DIRECTX:		throw UnimplementedFeatureException("DirectX FrameBuffer not implemented yet"); return nullptr;
			default:						return nullptr;
		};
	}
}