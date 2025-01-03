#include "core_pch.hpp"

namespace TE::Core
{
	std::shared_ptr<VertexBuffer> CreateVertexBuffer(uint32_t alloca_size)
	{
		switch( Renderer::API() )
		{
			case RENDERER_API_OPENGL: 				return std::make_shared<GL_VertexBuffer>(alloca_size);
			case RENDERER_API_VULKAN: 				throw UnimplementedFeatureException("Vulkan API is not implemented yet."); return nullptr;
			case RENDERER_API_DIRECTX: 				throw UnimplementedFeatureException("Direct3D API is not implemented yet."); return nullptr;
			default:								return nullptr;
		};
	}

	std::shared_ptr<VertexBuffer> CreateVertexBuffer(float* data, uint32_t size)
	{
		switch( Renderer::API() )
		{
			case RENDERER_API_OPENGL: 				return std::make_shared<GL_VertexBuffer>(data, size);
			case RENDERER_API_VULKAN: 				throw UnimplementedFeatureException("Vulkan API is not implemented yet."); return nullptr;
			case RENDERER_API_DIRECTX: 				throw UnimplementedFeatureException("Direct3D API is not implemented yet."); return nullptr;
			default:								return nullptr;
		};
	}

	std::shared_ptr<IndexBuffer> CreateIndexBuffer(uint32_t* data, uint32_t count)
	{
		switch( Renderer::API() )
		{
			case RENDERER_API_OPENGL: 				return std::make_shared<GL_IndexBuffer>(data, count);
			case RENDERER_API_VULKAN: 				throw UnimplementedFeatureException("Vulkan API is not implemented yet."); return nullptr;
			case RENDERER_API_DIRECTX: 				throw UnimplementedFeatureException("Direct3D API is not implemented yet."); return nullptr;
			default:								return nullptr;
		};
	}
}